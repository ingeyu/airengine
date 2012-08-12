#include "AirCommonNode.h"


namespace Air{
	
	namespace Common {
	
	    unsigned long Node::msNextGeneratedNameExt = 1;
		Node::QueuedUpdates Node::msQueuedUpdates;
	    //-----------------------------------------------------------------------
	    Node::Node()
			:mParent(0),
			mNeedParentUpdate(false),
			mNeedChildUpdate(false),
			mParentNotified(false),
	        mQueuedForUpdate(false),
			mPosition(Vector3(0,0,0)),
			mScale(Vector3(1,1,1)),
	        mInheritOrientation(true),
			mInheritScale(true),
			mDerivedPosition(Vector3(0,0,0)),
			mDerivedScale(Vector3(1,1,1)),
			mInitialPosition(Vector3(0,0,0)),
			mInitialScale(Vector3(1,1,1)),
			mCachedTransformOutOfDate(true),
			mListener(0)
	    {
	        // Generate a name
			std::stringstream str;
			str << "Unnamed_" << msNextGeneratedNameExt++;
	        mName = str.str();
	
	        needUpdate();
	
	    }
	    //-----------------------------------------------------------------------
		Node::Node(const AString& name):
			mParent(0),
			mNeedParentUpdate(false),
			mNeedChildUpdate(false),
			mParentNotified(false),
	        mQueuedForUpdate(false),
			mName(name),
			mScale(Vector3(1,1,1)),
	        mInheritOrientation(true),
			mInheritScale(true),
			mDerivedScale(Vector3(1,1,1)),
			mInitialScale(Vector3(1,1,1)),
			mCachedTransformOutOfDate(true),
			mListener(0)
	
	    {
	
	        needUpdate();
	
	    }
	
	    //-----------------------------------------------------------------------
	    Node::~Node()
	    {
			// Call listener (note, only called if there's something to do)
			if (mListener)
			{
				mListener->nodeDestroyed(this);
			}
	
			removeAllChildren();
			if(mParent)
				mParent->removeChild(this);
	
	        if (mQueuedForUpdate)
	        {
	            // Erase from queued updates
	            QueuedUpdates::iterator it =
	                std::find(msQueuedUpdates.begin(), msQueuedUpdates.end(), this);
	            assert(it != msQueuedUpdates.end());
	            if (it != msQueuedUpdates.end())
	            {
	                // Optimised algorithm to erase an element from unordered vector.
	                *it = msQueuedUpdates.back();
	                msQueuedUpdates.pop_back();
	            }
	        }
		}
	    //-----------------------------------------------------------------------
	    Node* Node::getParent(void) const
	    {
	        return mParent;
	    }
	
	    //-----------------------------------------------------------------------
	    void Node::setParent(Node* parent)
	    {
			bool different = (parent != mParent);
	
	        mParent = parent;
	        // Request update from parent
			mParentNotified = false ;
	        needUpdate();
	
			// Call listener (note, only called if there's something to do)
			if (mListener && different)
			{
				if (mParent)
					mListener->nodeAttached(this);
				else
					mListener->nodeDetached(this);
			}
	
	    }
	
	    //-----------------------------------------------------------------------
	    Matrix& Node::_getFullTransform(void)const{
	        if (mCachedTransformOutOfDate)
	        {
	            // Use derived values
	//             mCachedTransform.makeTransform(
	//                 _getDerivedPosition(),
	//                 _getDerivedScale(),
	//                 _getDerivedOrientation());
				Vector3&	v0	=	_getDerivedPosition();
				Vector3&	v1	=	_getDerivedScale();
				Quaternion&	q	=	_getDerivedOrientation();
				mCachedTransform	=	Matrix( v0,v1,q);
	            mCachedTransformOutOfDate = false;
	        }
	        return mCachedTransform;
	    }
	    //-----------------------------------------------------------------------
	    void Node::_update(bool updateChildren, bool parentHasChanged)
	    {
			// always clear information about parent notification
			mParentNotified = false ;
	
	        // Short circuit the off case
	        if (!updateChildren && !mNeedParentUpdate && !mNeedChildUpdate && !parentHasChanged )
	        {
	            return;
	        }
	
	
	        // See if we should process everyone
	        if (mNeedParentUpdate || parentHasChanged)
	        {
	            // Update transforms from parent
	            _updateFromParent();
			}
	
			if (mNeedChildUpdate || parentHasChanged)
			{
	
	            ChildNodeMap::iterator it, itend;
				itend = mChildren.end();
	            for (it = mChildren.begin(); it != itend; ++it)
	            {
	                Node* child = it->second;
	                child->_update(true, true);
	            }
	            mChildrenToUpdate.clear();
	        }
	        else
	        {
	            // Just update selected children
	
	            ChildUpdateSet::iterator it, itend;
				itend = mChildrenToUpdate.end();
	            for(it = mChildrenToUpdate.begin(); it != itend; ++it)
	            {
	                Node* child = *it;
	                child->_update(true, false);
	            }
	
	            mChildrenToUpdate.clear();
	        }
	
	        mNeedChildUpdate = false;
	
	    }
		//-----------------------------------------------------------------------
		void Node::_updateFromParent(void) const
		{
			updateFromParentImpl();
	
			// Call listener (note, this method only called if there's something to do)
			if (mListener)
			{
				mListener->nodeUpdated(this);
			}
		}
	    //-----------------------------------------------------------------------
	    void Node::updateFromParentImpl(void) const
	    {
	        if (mParent)
	        {
	            // Update orientation
	            Quaternion& parentOrientation = mParent->_getDerivedOrientation();
	            if (mInheritOrientation)
	            {
	                // Combine orientation with that of parent
	                mDerivedOrientation = parentOrientation * mOrientation;
	            }
				else
	            {
	                // No inheritence
	                mDerivedOrientation = mOrientation;
	            }
	
	            // Update scale
	            Vector3& parentScale = mParent->_getDerivedScale();
	            if (mInheritScale)
	            {
	                // Scale own position by parent scale, NB just combine
	                // as equivalent axes, no shearing
	                mDerivedScale = parentScale * mScale;
	            }
	            else
	            {
	                // No inheritence
	                mDerivedScale = mScale;
	            }
	
	            // Change position vector based on parent's orientation & scale
	            mDerivedPosition = parentOrientation * (parentScale * mPosition);
	
	            // Add altered position vector to parents
	            mDerivedPosition += mParent->_getDerivedPosition();
	        }
	        else
	        {
	            // Root node, no parent
	            mDerivedOrientation = mOrientation;
	            mDerivedPosition = mPosition;
	            mDerivedScale = mScale;
	        }
	
			mCachedTransformOutOfDate = true;
			mNeedParentUpdate = false;
	
	    }
	    //-----------------------------------------------------------------------
	    Node* Node::createChild(const Vector3& translate, const Quaternion& rotate)
	    {
	        Node* newNode = createChildImpl();
	        newNode->translate(translate);
	        newNode->rotate(rotate);
	        this->addChild(newNode);
	
	        return newNode;
	    }
	    //-----------------------------------------------------------------------
	    Node* Node::createChild(const AString& name, const Vector3& translate, const Quaternion& rotate)
	    {
	        Node* newNode = createChildImpl(name);
	        newNode->translate(translate);
	        newNode->rotate(rotate);
	        this->addChild(newNode);
	
	        return newNode;
	    }
	    //-----------------------------------------------------------------------
	    void Node::addChild(Node* child)
	    {
	        if (child->mParent)
	        {
	            child->removeChild(child);
	        }
	
	        mChildren.insert(ChildNodeMap::value_type(child->getName(), child));
	        child->setParent(this);
	
	    }
	    //-----------------------------------------------------------------------
	    unsigned short Node::numChildren(void) const
	    {
	        return static_cast< unsigned short >( mChildren.size() );
	    }
	    //-----------------------------------------------------------------------
	    Node* Node::getChild(unsigned short index) const
	    {
	        if( index < mChildren.size() )
	        {
	            ChildNodeMap::const_iterator i = mChildren.begin();
	            while (index--) ++i;
	            return i->second;
	        }
	        else
	            return NULL;
	    }
	    //-----------------------------------------------------------------------
	    Node* Node::removeChild(unsigned short index)
	    {
	        Node* ret;
	        if (index < mChildren.size())
	        {
	            ChildNodeMap::iterator i = mChildren.begin();
	            while (index--) ++i;
	            ret = i->second;
	            // cancel any pending update
	            cancelUpdate(ret);
	
	            mChildren.erase(i);
	            ret->setParent(NULL);
	            return ret;
	        }
	        else
	        {
				return	0;
	        }
	        return 0;
	    }
	    //-----------------------------------------------------------------------
	    Node* Node::removeChild(Node* child)
	    {
	        if (child)
	        {
	            ChildNodeMap::iterator i = mChildren.find(child->getName());
	            // ensure it's our child
	            if (i != mChildren.end() && i->second == child)
	            {
	                // cancel any pending update
	                cancelUpdate(child);
	
	                mChildren.erase(i);
	                child->setParent(NULL);
	            }
	        }
	        return child;
	    }
	    //-----------------------------------------------------------------------
	    const Quaternion& Node::getOrientation() const
	    {
	        return mOrientation;
	    }
	
	    //-----------------------------------------------------------------------
	    void Node::setOrientation( const Quaternion & q )
	    {
	        mOrientation = q;
			mOrientation.Normalize();
	        needUpdate();
	    }
	    //-----------------------------------------------------------------------
	    void Node::setOrientation( Real w, Real x, Real y, Real z)
	    {
	        mOrientation.w = w;
	        mOrientation.x = x;
	        mOrientation.y = y;
	        mOrientation.z = z;
	        needUpdate();
	    }
	    //-----------------------------------------------------------------------
	    void Node::resetOrientation(void)
	    {
	        mOrientation = Quaternion();
	        needUpdate();
	    }
	
	    //-----------------------------------------------------------------------
	    void Node::setPosition(const Vector3& pos)
	    {
	        mPosition = pos;
	        needUpdate();
	    }
	
	
	    //-----------------------------------------------------------------------
	    void Node::setPosition(Real x, Real y, Real z)
	    {
	        Vector3 v(x,y,z);
	        setPosition(v);
	    }
	
	    //-----------------------------------------------------------------------
	    const Vector3 & Node::getPosition(void) const
	    {
	        return mPosition;
	    }
	    //-----------------------------------------------------------------------
	    Matrix Node::getLocalAxes(void) const
	    {
	        Vector3 axisX = Vector3(1,0,0);
	        Vector3 axisY = Vector3(0,1,0);
	        Vector3 axisZ = Vector3(0,0,1);
	
	        axisX = mOrientation * axisX;
	        axisY = mOrientation * axisY;
	        axisZ = mOrientation * axisZ;
	
	        return Matrix(axisX.x, axisY.x, axisZ.x,0,
	                       axisX.y, axisY.y, axisZ.y,0,
	                       axisX.z, axisY.z, axisZ.z,0,
						   0,0,0,0);
	    }
	
	    //-----------------------------------------------------------------------
	    void Node::translate(const Vector3& d, TransformSpace relativeTo)
	    {
	        switch(relativeTo)
	        {
	        case TS_LOCAL:
	            // position is relative to parent so transform downwards
	            mPosition += mOrientation * d;
	        	break;
	        case TS_WORLD:
	            // position is relative to parent so transform upwards
	            if (mParent)
	            {
	                mPosition += (mParent->_getDerivedOrientation().Inverse() * d)
	                    / mParent->_getDerivedScale();
	            }
	            else
	            {
	                mPosition += d;
	            }
	        	break;
	        case TS_PARENT:
	            mPosition += d;
	            break;
	        }
	        needUpdate();
	
	    }
	    //-----------------------------------------------------------------------
	    void Node::translate(Real x, Real y, Real z, TransformSpace relativeTo)
	    {
	        Vector3 v(x,y,z);
	        translate(v, relativeTo);
	    }
	    //-----------------------------------------------------------------------
	    void Node::translate(const Matrix& axes, const Vector3& move, TransformSpace relativeTo)
	    {
	        Vector3 derived = axes * move;
	        translate(derived, relativeTo);
	    }
	    //-----------------------------------------------------------------------
	    void Node::translate(const Matrix& axes, Real x, Real y, Real z, TransformSpace relativeTo)
	    {
	        Vector3 d(x,y,z);
	        translate(axes,d,relativeTo);
	    }
	    //-----------------------------------------------------------------------
	    void Node::roll(const Real& angle, TransformSpace relativeTo)
	    {
	        rotate(Vector3(0,0,1), angle, relativeTo);
	    }
	    //-----------------------------------------------------------------------
	    void Node::pitch(const Real& angle, TransformSpace relativeTo)
	    {
	        rotate(Vector3(1,0,0), angle, relativeTo);
	    }
	    //-----------------------------------------------------------------------
	    void Node::yaw(const Real& angle, TransformSpace relativeTo)
	    {
	        rotate(Vector3(0,1,0), angle, relativeTo);
	
	    }
	    //-----------------------------------------------------------------------
	    void Node::rotate(const Vector3& axis, const Real& angle, TransformSpace relativeTo)
	    {
	        Quaternion q(axis,angle);
	        rotate(q, relativeTo);
	    }
	
	    //-----------------------------------------------------------------------
	    void Node::rotate(const Quaternion& q, TransformSpace relativeTo)
	    {
			// Normalise quaternion to avoid drift
			Quaternion qnorm = q;
			qnorm.Normalize();
	
	        switch(relativeTo)
	        {
	        case TS_PARENT:
	            // Rotations are normally relative to local axes, transform up
	            mOrientation = qnorm * mOrientation;
	            break;
	        case TS_WORLD:
	            // Rotations are normally relative to local axes, transform up
	            mOrientation = mOrientation * _getDerivedOrientation().Inverse()
	                * qnorm * _getDerivedOrientation();
	            break;
	        case TS_LOCAL:
	            // Note the order of the mult, i.e. q comes after
	            mOrientation = mOrientation * qnorm;
	            break;
	        }
	        needUpdate();
	    }
	    //-----------------------------------------------------------------------
	    Quaternion & Node::_getDerivedOrientation(void)const
	    {
			if (mNeedParentUpdate)
			{
	        	_updateFromParent();
			}
	        return mDerivedOrientation;
	    }
	    //-----------------------------------------------------------------------
	    Vector3 & Node::_getDerivedPosition(void)const
	    {
			if (mNeedParentUpdate)
			{
	        	_updateFromParent();
			}
	        return mDerivedPosition;
	    }
	    //-----------------------------------------------------------------------
	    Vector3 & Node::_getDerivedScale(void)const
	    {
	        if (mNeedParentUpdate)
	        {
	            _updateFromParent();
	        }
	        return mDerivedScale;
	    }
	    //-----------------------------------------------------------------------
	    void Node::removeAllChildren(void)
	    {
			ChildNodeMap::iterator i, iend;
			iend = mChildren.end();
			for (i = mChildren.begin(); i != iend; ++i)
			{
				i->second->setParent(0);
			}
	        mChildren.clear();
			mChildrenToUpdate.clear();
	    }
	    //-----------------------------------------------------------------------
	    void Node::setScale(const Vector3& scale)
	    {
	        mScale = scale;
	        needUpdate();
	    }
	    //-----------------------------------------------------------------------
	    void Node::setScale(Real x, Real y, Real z)
	    {
	        mScale.x = x;
	        mScale.y = y;
	        mScale.z = z;
	        needUpdate();
	    }
	    //-----------------------------------------------------------------------
	    const Vector3 & Node::getScale(void) const
	    {
	        return mScale;
	    }
	    //-----------------------------------------------------------------------
	    void Node::setInheritOrientation(bool inherit)
	    {
	        mInheritOrientation = inherit;
	        needUpdate();
	    }
	    //-----------------------------------------------------------------------
	    bool Node::getInheritOrientation(void) const
	    {
	        return mInheritOrientation;
	    }
	    //-----------------------------------------------------------------------
	    void Node::setInheritScale(bool inherit)
	    {
	        mInheritScale = inherit;
	        needUpdate();
	    }
	    //-----------------------------------------------------------------------
	    bool Node::getInheritScale(void) const
	    {
	        return mInheritScale;
	    }
	    //-----------------------------------------------------------------------
	    void Node::scale(const Vector3& scale)
	    {
	        mScale *= scale;
	        needUpdate();
	
	    }
	    //-----------------------------------------------------------------------
	    void Node::scale(Real x, Real y, Real z)
	    {
	        mScale.x *= x;
	        mScale.y *= y;
	        mScale.z *= z;
	        needUpdate();
	
	    }
	    //-----------------------------------------------------------------------
	    const AString& Node::getName(void) const
	    {
	        return mName;
	    }
	
	    //-----------------------------------------------------------------------
	    void Node::getWorldTransforms(Matrix* xform) const
	    {
	        // Assumes up to date
	        *xform = this->_getFullTransform();
	    }
	    //-----------------------------------------------------------------------
	    void Node::setInitialState(void)
	    {
	        mInitialPosition = mPosition;
	        mInitialOrientation = mOrientation;
	        mInitialScale = mScale;
	    }
	    //-----------------------------------------------------------------------
	    void Node::resetToInitialState(void)
	    {
	        mPosition = mInitialPosition;
	        mOrientation = mInitialOrientation;
	        mScale = mInitialScale;
	
	        needUpdate();
	    }
	    //-----------------------------------------------------------------------
	    const Vector3& Node::getInitialPosition(void) const
	    {
	        return mInitialPosition;
	    }
	    //-----------------------------------------------------------------------
	    const Quaternion& Node::getInitialOrientation(void) const
	    {
	        return mInitialOrientation;
	
	    }
	    //-----------------------------------------------------------------------
	    const Vector3& Node::getInitialScale(void) const
	    {
	        return mInitialScale;
	    }
	    //-----------------------------------------------------------------------
	    Node* Node::getChild(const AString& name) const
	    {
	        ChildNodeMap::const_iterator i = mChildren.find(name);
	
	        if (i == mChildren.end())
	        {
				return	NULL;
	        }
	        return i->second;
	
	    }
	    //-----------------------------------------------------------------------
	    Node* Node::removeChild(const AString& name)
	    {
	        ChildNodeMap::iterator i = mChildren.find(name);
	
	        if (i == mChildren.end())
	        {
	
				return	NULL;
	        }
	
	        Node* ret = i->second;
	        // Cancel any pending update
	        cancelUpdate(ret);
	
	        mChildren.erase(i);
	        ret->setParent(NULL);
	
	        return ret;
	
	
	    }
	
	    //-----------------------------------------------------------------------
	
	    //-----------------------------------------------------------------------
	    void Node::needUpdate(bool forceParentUpdate)
	    {
	
	        mNeedParentUpdate = true;
			mNeedChildUpdate = true;
	        mCachedTransformOutOfDate = true;
	
	        // Make sure we're not root and parent hasn't been notified before
	        if (mParent && (!mParentNotified || forceParentUpdate))
	        {
	            mParent->requestUpdate(this, forceParentUpdate);
				mParentNotified = true ;
	        }
	
	        // all children will be updated
	        mChildrenToUpdate.clear();
	    }
	    //-----------------------------------------------------------------------
	    void Node::requestUpdate(Node* child, bool forceParentUpdate)
	    {
	        // If we're already going to update everything this doesn't matter
	        if (mNeedChildUpdate)
	        {
	            return;
	        }
	
	        mChildrenToUpdate.insert(child);
	        // Request selective update of me, if we didn't do it before
	        if (mParent && (!mParentNotified || forceParentUpdate))
			{
	            mParent->requestUpdate(this, forceParentUpdate);
				mParentNotified = true ;
			}
	
	    }
	    //-----------------------------------------------------------------------
	    void Node::cancelUpdate(Node* child)
	    {
	        mChildrenToUpdate.erase(child);
	
	        // Propogate this up if we're done
	        if (mChildrenToUpdate.empty() && mParent && !mNeedChildUpdate)
	        {
	            mParent->cancelUpdate(this);
				mParentNotified = false ;
	        }
	    }
		//-----------------------------------------------------------------------
		void Node::queueNeedUpdate(Node* n)
		{
	        // Don't queue the node more than once
	        if (!n->mQueuedForUpdate)
	        {
	            n->mQueuedForUpdate = true;
			    msQueuedUpdates.push_back(n);
	        }
		}
		//-----------------------------------------------------------------------
		void Node::processQueuedUpdates(void)
		{
			for (QueuedUpdates::iterator i = msQueuedUpdates.begin();
				i != msQueuedUpdates.end(); ++i)
			{
				// Update, and force parent update since chances are we've ended
				// up with some mixed state in there due to re-entrancy
	            Node* n = *i;
	            n->mQueuedForUpdate = false;
				n->needUpdate(true);
			}
			msQueuedUpdates.clear();
		}
	    //-----------------------------------------------------------------------
	
	}
	
};
