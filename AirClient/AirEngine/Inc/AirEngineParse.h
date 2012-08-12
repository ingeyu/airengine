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

#ifndef __EngineParse_H__
#define __EngineParse_H__

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirEngineDataStream.h"
namespace Air{
	
	namespace Client {
	
	    /** Generic class for serialising data to / from binary stream-based files.
	    @remarks
	        This class provides a number of useful methods for exporting / importing data
	        from stream-oriented binary files (e.g. .mesh and .skeleton).
	    */
		class ENGINE_EXPORT Parse //: public SerializerAlloc
	    {
	    public:
	        Parse();
	        virtual ~Parse();
	
			/// The endianness of written files
			enum Endian
			{
				/// Use the platform native endian
				ENDIAN_NATIVE,
				/// Use big endian (0x1000 is serialised as 0x10 0x00)
				ENDIAN_BIG,
				/// Use little endian (0x1000 is serialised as 0x00 0x10)
				ENDIAN_LITTLE
			};
	
	
	    protected:
	
	        UInt mCurrentstreamLen;
	        FILE* mpfFile;
	        AString mVersion;
			U1 mFlipEndian; // default to native endian, derive from header
	
	        // Internal methods
	        virtual void writeFileHeader(void);
	        virtual void writeChunkHeader(U16 id, UInt size);
	        
	        void writeFloats(const Real* const pfloat, UInt count);
	        void writeFloats(const double* const pfloat, UInt count);
	        void writeShorts(const U16* const pShort, UInt count);
	        void writeInts(const UInt* const pInt, UInt count); 
	        void writeBools(const U1* const pLong, UInt count);
	        void writeObject(const Float3& vec);
	        void writeObject(const Float4& q);
	        
	        void writeString(const AString& string);
	        void writeData(const void* const buf, UInt size, UInt count);
	        
	        virtual void readFileHeader(DataStreamPtr& stream);
	        virtual unsigned short readChunk(DataStreamPtr& stream);
	        
	        void readBools(DataStreamPtr& stream, U1* pDest, UInt count);
	        void readFloats(DataStreamPtr& stream, Real* pDest, UInt count);
	        void readFloats(DataStreamPtr& stream, double* pDest, UInt count);
	        void readShorts(DataStreamPtr& stream, U16* pDest, UInt count);
	        void readInts(DataStreamPtr& stream, UInt* pDest, UInt count);
	        void readObject(DataStreamPtr& stream, Float3& pDest);
	        void readObject(DataStreamPtr& stream, Float4& pDest);
	
	        AString readString(DataStreamPtr& stream);
	        AString readString(DataStreamPtr& stream, UInt numChars);
	        
	        virtual void flipToLittleEndian(void* pData, UInt size, UInt count = 1);
	        virtual void flipFromLittleEndian(void* pData, UInt size, UInt count = 1);
	        
	        virtual void flipEndian(void * pData, UInt size, UInt count);
	        virtual void flipEndian(void * pData, UInt size);
	
			/// Determine the endianness of the incoming stream compared to native
			virtual void determineEndianness(DataStreamPtr& stream);
			/// Determine the endianness to write with based on option
			virtual void determineEndianness(Endian requestedEndian);
	    };
	
	}
};


#endif
