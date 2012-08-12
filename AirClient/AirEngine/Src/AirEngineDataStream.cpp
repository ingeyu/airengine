/*
-----------------------------------------------------------------------------
This source file is part of OGRE 
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

This program is free software; you can redistribute it and/or modify it under 
the terms of the GNU Lesser General Public License as published by the Free Software 
Foundation; either version 2 of the License, or (at your option) any later 
version.

This program is distributed in the hope that it will be useful, but WITHOUT 
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with 
this program; if not, write to the Free Software Foundation, Inc., 59 Temple 
Place - Suite 330, Boston, MA 02111-1307, USA, or go to 
http://www.gnu.org/copyleft/lesser.txt.

You may alternatively use this source under the terms of a specific version of
the OGRE Unrestricted License provided you have obtained such a license from
Torus Knot Software Ltd.
-----------------------------------------------------------------------------
*/
#include "AirEngineDataStream.h"
#include "AirCommonConverter.h"
#include <iostream>
#include <fstream>
namespace Air{
	
	namespace Client {
	
	    //-----------------------------------------------------------------------
	    //-----------------------------------------------------------------------
	    template <typename T> DataStream& DataStream::operator >>(T& val)
	    {
	        read(static_cast<void*>(&val), sizeof(T));
	        return *this;
	    }
	    //-----------------------------------------------------------------------
	    AString DataStream::getLine(U1 trimAfter)
	    {
	        char tmpBuf[OGRE_STREAM_TEMP_SIZE];
	        AString retString;
	        UInt readCount;
	        // Keep looping while not hitting delimiter
	        while ((readCount = read(tmpBuf, OGRE_STREAM_TEMP_SIZE-1)) != 0)
	        {
	            // Terminate string
	            tmpBuf[readCount] = '\0';
	
	            char* p = strchr(tmpBuf, '\n');
	            if (p != 0)
	            {
	                // Reposition backwards
	                skip((long)(p + 1 - tmpBuf - readCount));
	                *p = '\0';
	            }
	
	            retString += tmpBuf;
	
	            if (p != 0)
	            {
	                // Trim off trailing CR if this was a CR/LF entry
	                if (retString.length() && retString[retString.length()-1] == '\r')
	                {
	                    retString.erase(retString.length()-1, 1);
	                }
	
	                // Found terminator, break out
	                break;
	            }
	        }
	
	        if (trimAfter)
	        {
				//Common::StringUtil::trim(retString);
	        }
	
	        return retString;
	    }
	    //-----------------------------------------------------------------------
	    UInt DataStream::readLine(char* buf, UInt maxCount, const AString& delim)
	    {
			// Deal with both Unix & Windows LFs
			U1 trimCR = false;
			if (delim.find_first_of('\n') != AString::npos)
			{
				trimCR = true;
			}
	
	        char tmpBuf[OGRE_STREAM_TEMP_SIZE];
	        UInt chunkSize = min(maxCount, (UInt)OGRE_STREAM_TEMP_SIZE-1);
	        UInt totalCount = 0;
	        UInt readCount; 
	        while (chunkSize && (readCount = read(tmpBuf, chunkSize)))
	        {
	            // Terminate
	            tmpBuf[readCount] = '\0';
	
	            // Find first delimiter
	            UInt pos = strcspn(tmpBuf, delim.c_str());
	
	            if (pos < readCount)
	            {
	                // Found terminator, reposition backwards
	                skip((long)(pos + 1 - readCount));
	            }
	
	            // Are we genuinely copying?
	            if (buf)
	            {
	                memcpy(buf+totalCount, tmpBuf, pos);
	            }
	            totalCount += pos;
	
	            if (pos < readCount)
	            {
	                // Trim off trailing CR if this was a CR/LF entry
	                if (trimCR && totalCount && buf[totalCount-1] == '\r')
	                {
	                    --totalCount;
	                }
	
	                // Found terminator, break out
	                break;
	            }
	
	            // Adjust chunkSize for next time
	            chunkSize = min(maxCount-totalCount, (UInt)OGRE_STREAM_TEMP_SIZE-1);
	        }
	
	        // Terminate
	        buf[totalCount] = '\0';
	
	        return totalCount;
	    }
	    //-----------------------------------------------------------------------
	    UInt DataStream::skipLine(const AString& delim)
	    {
	        char tmpBuf[OGRE_STREAM_TEMP_SIZE];
	        UInt total = 0;
	        UInt readCount;
	        // Keep looping while not hitting delimiter
	        while ((readCount = read(tmpBuf, OGRE_STREAM_TEMP_SIZE-1)) != 0)
	        {
	            // Terminate string
	            tmpBuf[readCount] = '\0';
	
	            // Find first delimiter
	            UInt pos = strcspn(tmpBuf, delim.c_str());
	
	            if (pos < readCount)
	            {
	                // Found terminator, reposition backwards
	                skip((long)(pos + 1 - readCount));
	
	                total += pos + 1;
	
	                // break out
	                break;
	            }
	
	            total += readCount;
	        }
	
	        return total;
	    }
	    //-----------------------------------------------------------------------
	    AString DataStream::getAsString(void)
	    {
	        // Read the entire buffer
	        char* pBuf = new char[mSize+1];//OGRE_ALLOC_T(char, mSize+1, MEMCATEGORY_GENERAL);
	        // Ensure read from begin of stream
	        seek(0);
	        read(pBuf, mSize);
	        pBuf[mSize] = '\0';
	        AString str;
	        str.insert(0, pBuf, mSize);
	        delete[] pBuf;//(pBuf, MEMCATEGORY_GENERAL);
	        return str;
	    }
	    //-----------------------------------------------------------------------
	    //-----------------------------------------------------------------------
	    MemoryDataStream::MemoryDataStream(void* pMem, UInt size, U1 freeOnClose)
	        : DataStream()
	    {
	        mData = mPos = static_cast<U8*>(pMem);
	        mSize = size;
	        mEnd = mData + mSize;
	        mFreeOnClose = freeOnClose;
	        assert(mEnd >= mPos);
	    }
	    //-----------------------------------------------------------------------
	    MemoryDataStream::MemoryDataStream(const AString& name, void* pMem, UInt size, 
	        U1 freeOnClose)
	        : DataStream(name)
	    {
	        mData = mPos = static_cast<U8*>(pMem);
	        mSize = size;
	        mEnd = mData + mSize;
	        mFreeOnClose = freeOnClose;
	        assert(mEnd >= mPos);
	    }
	    //-----------------------------------------------------------------------
	    MemoryDataStream::MemoryDataStream(DataStream& sourceStream, 
	        U1 freeOnClose)
	        : DataStream()
	    {
	        // Copy data from incoming stream
	        mSize = sourceStream.size();
	        mData = OGRE_ALLOC_T(U8, mSize, MEMCATEGORY_GENERAL);
	        mPos = mData;
	        mEnd = mData + sourceStream.read(mData, mSize);
	        mFreeOnClose = freeOnClose;
	        assert(mEnd >= mPos);
	    }
	    //-----------------------------------------------------------------------
	    MemoryDataStream::MemoryDataStream(DataStreamPtr& sourceStream, 
	        U1 freeOnClose)
	        : DataStream()
	    {
	        // Copy data from incoming stream
	        mSize = sourceStream->size();
	        mData = OGRE_ALLOC_T(U8, mSize, MEMCATEGORY_GENERAL);
	        mPos = mData;
	        mEnd = mData + sourceStream->read(mData, mSize);
	        mFreeOnClose = freeOnClose;
	        assert(mEnd >= mPos);
	    }
	    //-----------------------------------------------------------------------
	    MemoryDataStream::MemoryDataStream(const AString& name, DataStream& sourceStream, 
	        U1 freeOnClose)
	        : DataStream(name)
	    {
	        // Copy data from incoming stream
	        mSize = sourceStream.size();
	        mData = OGRE_ALLOC_T(U8, mSize, MEMCATEGORY_GENERAL);
	        mPos = mData;
	        mEnd = mData + sourceStream.read(mData, mSize);
	        mFreeOnClose = freeOnClose;
	        assert(mEnd >= mPos);
	    }
	    //-----------------------------------------------------------------------
	    MemoryDataStream::MemoryDataStream(const AString& name, const DataStreamPtr& sourceStream, 
	        U1 freeOnClose)
	        : DataStream(name)
	    {
	        // Copy data from incoming stream
	        mSize = sourceStream->size();
	        mData = OGRE_ALLOC_T(U8, mSize, MEMCATEGORY_GENERAL);
	        mPos = mData;
	        mEnd = mData + sourceStream->read(mData, mSize);
	        mFreeOnClose = freeOnClose;
	        assert(mEnd >= mPos);
	    }
	    //-----------------------------------------------------------------------
	    MemoryDataStream::MemoryDataStream(UInt size, U1 freeOnClose)
	        : DataStream()
	    {
	        mSize = size;
	        mFreeOnClose = freeOnClose;
	        mData = OGRE_ALLOC_T(U8, mSize, MEMCATEGORY_GENERAL);
	        mPos = mData;
	        mEnd = mData + mSize;
	        assert(mEnd >= mPos);
	    }
	    //-----------------------------------------------------------------------
	    MemoryDataStream::MemoryDataStream(const AString& name, UInt size, 
	        U1 freeOnClose)
	        : DataStream(name)
	    {
	        mSize = size;
	        mFreeOnClose = freeOnClose;
	        mData = OGRE_ALLOC_T(U8, mSize, MEMCATEGORY_GENERAL);
	        mPos = mData;
	        mEnd = mData + mSize;
	        assert(mEnd >= mPos);
	    }
	    //-----------------------------------------------------------------------
	    MemoryDataStream::~MemoryDataStream()
	    {
	        close();
	    }
	    //-----------------------------------------------------------------------
	    UInt MemoryDataStream::read(void* buf, UInt count)
	    {
	        UInt cnt = count;
	        // Read over end of memory?
	        if (mPos + cnt > mEnd)
	            cnt = mEnd - mPos;
	        if (cnt == 0)
	            return 0;
	
	        assert (cnt<=count);
	
	        memcpy(buf, mPos, cnt);
	        mPos += cnt;
	        return cnt;
	    }
	    //-----------------------------------------------------------------------
	    UInt MemoryDataStream::readLine(char* buf, UInt maxCount, 
	        const AString& delim)
	    {
	        // Deal with both Unix & Windows LFs
			U1 trimCR = false;
			if (delim.find_first_of('\n') != AString::npos)
			{
				trimCR = true;
			}
	
	        UInt pos = 0;
	
	        // Make sure pos can never go past the end of the data 
	        while (pos < maxCount && mPos < mEnd)
	        {
	            if (delim.find(*mPos) != AString::npos)
	            {
	                // Trim off trailing CR if this was a CR/LF entry
	                if (trimCR && pos && buf[pos-1] == '\r')
	                {
	                    // terminate 1 character early
	                    --pos;
	                }
	
	                // Found terminator, skip and break out
	                ++mPos;
	                break;
	            }
	
	            buf[pos++] = *mPos++;
	        }
	
	        // terminate
	        buf[pos] = '\0';
	
	        return pos;
	    }
	    //-----------------------------------------------------------------------
	    UInt MemoryDataStream::skipLine(const AString& delim)
	    {
	        UInt pos = 0;
	
	        // Make sure pos can never go past the end of the data 
	        while (mPos < mEnd)
	        {
	            ++pos;
	            if (delim.find(*mPos++) != AString::npos)
	            {
	                // Found terminator, break out
	                break;
	            }
	        }
	
	        return pos;
	
	    }
	    //-----------------------------------------------------------------------
	    void MemoryDataStream::skip(long count)
	    {
	        UInt newpos = (UInt)( ( mPos - mData ) + count );
	        assert( mData + newpos <= mEnd );        
	
	        mPos = mData + newpos;
	    }
	    //-----------------------------------------------------------------------
	    void MemoryDataStream::seek( UInt pos )
	    {
	        assert( mData + pos <= mEnd );
	        mPos = mData + pos;
	    }
	    //-----------------------------------------------------------------------
	    UInt MemoryDataStream::tell(void) const
		{
			//mData is start, mPos is current location
			return mPos - mData;
		}
		//-----------------------------------------------------------------------
	    U1 MemoryDataStream::eof(void) const
	    {
	        return mPos >= mEnd;
	    }
	    //-----------------------------------------------------------------------
	    void MemoryDataStream::close(void)    
	    {
	        if (mFreeOnClose && mData)
	        {
	            OGRE_FREE(mData, MEMCATEGORY_GENERAL);
	            mData = 0;
	        }
	
	    }
	    //-----------------------------------------------------------------------
	    //-----------------------------------------------------------------------
	    FileStreamDataStream::FileStreamDataStream(std::ifstream* s, U1 freeOnClose)
	        : DataStream(), mpStream(s), mFreeOnClose(freeOnClose)
	    {
	        // calculate the size
	        mpStream->seekg(0, std::ios_base::end);
	        mSize = mpStream->tellg();
	        mpStream->seekg(0, std::ios_base::beg);
	
	    }
	    //-----------------------------------------------------------------------
	    FileStreamDataStream::FileStreamDataStream(const AString& name, 
	        std::ifstream* s, U1 freeOnClose)
	        : DataStream(name), mpStream(s), mFreeOnClose(freeOnClose)
	    {
	        // calculate the size
	        mpStream->seekg(0, std::ios_base::end);
	        mSize = mpStream->tellg();
	        mpStream->seekg(0, std::ios_base::beg);
	    }
	    //-----------------------------------------------------------------------
	    FileStreamDataStream::FileStreamDataStream(const AString& name, 
	        std::ifstream* s, UInt size, U1 freeOnClose)
	        : DataStream(name), mpStream(s), mFreeOnClose(freeOnClose)
	    {
	        // Size is passed in
	        mSize = size;
	    }
	    //-----------------------------------------------------------------------
	    FileStreamDataStream::~FileStreamDataStream()
	    {
	        close();
	    }
	    //-----------------------------------------------------------------------
	    UInt FileStreamDataStream::read(void* buf, UInt count)
	    {
			mpStream->read(static_cast<char*>(buf), static_cast<std::streamsize>(count));
	        return mpStream->gcount();
	    }
	    //-----------------------------------------------------------------------
	    UInt FileStreamDataStream::readLine(char* buf, UInt maxCount, 
	        const AString& delim)
	    {
			if (delim.empty())
			{
				OGRE_EXCEPT(0, "No delimiter provided",
					"FileStreamDataStream::readLine");
			}
			if (delim.size() > 1)
			{
				LogManager(
					"WARNING: FileStreamDataStream::readLine - using only first delimeter");
			}
			// Deal with both Unix & Windows LFs
			U1 trimCR = false;
			if (delim.at(0) == '\n') 
			{
				trimCR = true;
			}
			// maxCount + 1 since count excludes terminator in getline
			mpStream->getline(buf, static_cast<std::streamsize>(maxCount+1), delim.at(0));
			UInt ret = mpStream->gcount();
			// three options
			// 1) we had an eof before we read a whole line
			// 2) we ran out of buffer space
			// 3) we read a whole line - in this case the delim character is taken from the stream but not written in the buffer so the read data is of length ret-1 and thus ends at index ret-2
			// in all cases the buffer will be null terminated for us
	
			if (mpStream->eof()) 
			{
				// no problem
			}
			else if (mpStream->fail())
			{
				// Did we fail because of maxCount hit? No - no terminating character
				// in included in the count in this case
				if (ret == maxCount)
				{
					// clear failbit for next time 
					mpStream->clear();
				}
				else
				{
					OGRE_EXCEPT(0, 
						"Streaming error occurred", 
						"FileStreamDataStream::readLine");
				}
			}
			else 
			{
				// we need to adjust ret because we want to use it as a
				// pointer to the terminating null character and it is
				// currently the length of the data read from the stream
				// i.e. 1 more than the length of the data in the buffer and
				// hence 1 more than the _index_ of the NULL character
				--ret;
			}
	
			// trim off CR if we found CR/LF
			if (trimCR && buf[ret-1] == '\r')
			{
				--ret;
				buf[ret] = '\0';
			}
			return ret;
		}
	    //-----------------------------------------------------------------------
	    void FileStreamDataStream::skip(long count)
	    {
	#if defined(STLPORT)
			// Workaround for STLport issues: After reached eof of file stream,
			// it's seems the stream was putted in intermediate state, and will be
			// fail if try to repositioning relative to current position.
			// Note: tellg() fail in this case too.
			if (mpStream->eof())
			{
				mpStream->clear();
				// Use seek relative to either begin or end to bring the stream
				// back to normal state.
				mpStream->seekg(0, std::ios::end);
			}
	#endif 		
			mpStream->clear(); //Clear fail status in case eof was set
			mpStream->seekg(static_cast<std::ifstream::pos_type>(count), std::ios::cur);
	    }
	    //-----------------------------------------------------------------------
	    void FileStreamDataStream::seek( UInt pos )
	    {
			mpStream->clear(); //Clear fail status in case eof was set
	        mpStream->seekg(static_cast<std::streamoff>(pos), std::ios::beg);
	    }
		//-----------------------------------------------------------------------
	    UInt FileStreamDataStream::tell(void) const
		{
			mpStream->clear(); //Clear fail status in case eof was set
			return mpStream->tellg();
		}
		//-----------------------------------------------------------------------
	    U1 FileStreamDataStream::eof(void) const
	    {
	        return mpStream->eof();
	    }
	    //-----------------------------------------------------------------------
	    void FileStreamDataStream::close(void)
	    {
	        if (mpStream)
	        {
	            mpStream->close();
	            if (mFreeOnClose)
	            {
	                // delete the stream too
	                OGRE_DELETE_T(mpStream, basic_ifstream, MEMCATEGORY_GENERAL);
	                mpStream = 0;
	            }
	        }
	    }
	    //-----------------------------------------------------------------------
	    //-----------------------------------------------------------------------
	    FileHandleDataStream::FileHandleDataStream(FILE* handle)
	        : DataStream(), mFileHandle(handle)
	    {
			// Determine size
			fseek(mFileHandle, 0, SEEK_END);
			mSize = ftell(mFileHandle);
			fseek(mFileHandle, 0, SEEK_SET);
	    }
	    //-----------------------------------------------------------------------
	    FileHandleDataStream::FileHandleDataStream(const AString& name, FILE* handle)
	        : DataStream(name), mFileHandle(handle)
	    {
			// Determine size
			fseek(mFileHandle, 0, SEEK_END);
			mSize = ftell(mFileHandle);
			fseek(mFileHandle, 0, SEEK_SET);
	    }
	    //-----------------------------------------------------------------------
	    FileHandleDataStream::~FileHandleDataStream()
	    {
	        close();
	    }
	    //-----------------------------------------------------------------------
	    UInt FileHandleDataStream::read(void* buf, UInt count)
	    {
	        return fread(buf, 1, count, mFileHandle);
	    }
	    //-----------------------------------------------------------------------
	    void FileHandleDataStream::skip(long count)
	    {
	        fseek(mFileHandle, count, SEEK_CUR);
	    }
	    //-----------------------------------------------------------------------
	    void FileHandleDataStream::seek( UInt pos )
	    {
	        fseek(mFileHandle, static_cast<long>(pos), SEEK_SET);
	    }
	    //-----------------------------------------------------------------------
	    UInt FileHandleDataStream::tell(void) const
		{
			return ftell( mFileHandle );
		}
		//-----------------------------------------------------------------------
	    U1 FileHandleDataStream::eof(void) const
	    {
	        return feof(mFileHandle) != 0;
	    }
	    //-----------------------------------------------------------------------
	    void FileHandleDataStream::close(void)
	    {
	        fclose(mFileHandle);
	        mFileHandle = 0;
	    }
	    //-----------------------------------------------------------------------
	
	}
};
