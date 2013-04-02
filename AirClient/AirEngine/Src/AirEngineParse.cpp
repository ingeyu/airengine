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
#include "AirEngineParse.h"
#include "AirEngineDataStream.h"

namespace Air{
	
	namespace Engine {
	
	    /// stream overhead = ID + size
	    const UInt STREAM_OVERHEAD_SIZE = sizeof(U16) + sizeof(UInt);
	    const U16 HEADER_STREAM_ID = 0x1000;
	    const U16 OTHER_ENDIAN_HEADER_STREAM_ID = 0x0010;
	    //---------------------------------------------------------------------
	    Parse::Parse()
	    {
	        // Version number
	        mVersion = "[Serializer_v1.00]";
			mFlipEndian = false;
	    }
	    //---------------------------------------------------------------------
	    Parse::~Parse()
	    {
	    }
	    //---------------------------------------------------------------------
		void Parse::determineEndianness(DataStreamPtr& stream)
		{
			if (stream->tell() != 0)
			{
				OGRE_EXCEPT(0,
					"Can only determine the endianness of the input stream if it "
					"is at the start", "Parse::determineEndianness");
			}
					
			U16 dest;
			// read header id manually (no conversion)
	        UInt actually_read = stream->read(&dest, sizeof(U16));
			// skip back
	        stream->skip(0 - (long)actually_read);
	        if (actually_read != sizeof(U16))
	        {
	            // end of file?
	            OGRE_EXCEPT(0,
	                        "Couldn't read 16 bit header value from input stream.",
	                        "Parse::determineEndianness");
	        }
			if (dest == HEADER_STREAM_ID)
			{
				mFlipEndian = false;
			}
			else if (dest == OTHER_ENDIAN_HEADER_STREAM_ID)
			{
				mFlipEndian = true;
			}
			else
			{
				OGRE_EXCEPT(0,
					"Header chunk didn't match either endian: Corrupted stream?",
					"Parse::determineEndianness");
			}
		}
	    //---------------------------------------------------------------------
		void Parse::determineEndianness(Endian requestedEndian)
		{
			switch(requestedEndian)
			{
			case ENDIAN_NATIVE:
				mFlipEndian = false;
				break;
			case ENDIAN_BIG:
	#if OGRE_ENDIAN == OGRE_ENDIAN_BIG
				mFlipEndian = false;
	#else
				mFlipEndian = true;
	#endif
				break;
			case ENDIAN_LITTLE:
	#if OGRE_ENDIAN == OGRE_ENDIAN_BIG
				mFlipEndian = true;
	#else
				mFlipEndian = false;
	#endif
				break;
			}
		}
	    //---------------------------------------------------------------------
	    void Parse::writeFileHeader(void)
	    {
	        
	        U16 val = HEADER_STREAM_ID;
	        writeShorts(&val, 1);
	
	        writeString(mVersion);
	
	    }
	    //---------------------------------------------------------------------
	    void Parse::writeChunkHeader(U16 id, UInt size)
	    {
	        writeShorts(&id, 1);
			UInt uint32size = static_cast<UInt>(size);
	        writeInts(&uint32size, 1);
	    }
	    //---------------------------------------------------------------------
	    void Parse::writeFloats(const Real* const pFloat, UInt count)
	    {
			if (mFlipEndian)
			{
	            Real * pFloatToWrite = (Real *)malloc(sizeof(Real) * count);
	            memcpy(pFloatToWrite, pFloat, sizeof(Real) * count);
	            
	            flipToLittleEndian(pFloatToWrite, sizeof(Real), count);
	            writeData(pFloatToWrite, sizeof(Real), count);
	            
	            free(pFloatToWrite);
			}
			else
			{
	            writeData(pFloat, sizeof(Real), count);
			}
	    }
	    //---------------------------------------------------------------------
	    void Parse::writeFloats(const double* const pDouble, UInt count)
	    {
			// Convert to Real, then write
			Real* tmp = OGRE_ALLOC_T(Real, count, MEMCATEGORY_GENERAL);
			for (unsigned int i = 0; i < count; ++i)
			{
				tmp[i] = static_cast<Real>(pDouble[i]);
			}
			if(mFlipEndian)
			{
	            flipToLittleEndian(tmp, sizeof(Real), count);
	            writeData(tmp, sizeof(Real), count);
			}
			else
			{
	            writeData(tmp, sizeof(Real), count);
			}
			OGRE_FREE(tmp, MEMCATEGORY_GENERAL);
	    }
	    //---------------------------------------------------------------------
	    void Parse::writeShorts(const U16* const pShort, UInt count = 1)
	    {
			if(mFlipEndian)
			{
	            unsigned short * pShortToWrite = (unsigned short *)malloc(sizeof(unsigned short) * count);
	            memcpy(pShortToWrite, pShort, sizeof(unsigned short) * count);
	            
	            flipToLittleEndian(pShortToWrite, sizeof(unsigned short), count);
	            writeData(pShortToWrite, sizeof(unsigned short), count);
	            
	            free(pShortToWrite);
			}
			else
			{
	            writeData(pShort, sizeof(unsigned short), count);
			}
	    }
	    //---------------------------------------------------------------------
	    void Parse::writeInts(const UInt* const pInt, UInt count = 1)
	    {
			if(mFlipEndian)
			{
	            unsigned int * pIntToWrite = (unsigned int *)malloc(sizeof(unsigned int) * count);
	            memcpy(pIntToWrite, pInt, sizeof(unsigned int) * count);
	            
	            flipToLittleEndian(pIntToWrite, sizeof(unsigned int), count);
	            writeData(pIntToWrite, sizeof(unsigned int), count);
	            
	            free(pIntToWrite);
			}
			else
			{
	            writeData(pInt, sizeof(unsigned int), count);
			}
	    }
	    //---------------------------------------------------------------------
	    //---------------------------------------------------------------------
	    void Parse::writeBools(const U1* const pBool, UInt count = 1)
	    {
	    //no endian flipping for 1-byte bools
	    //XXX Nasty Hack to convert to 1-byte bools
	#	if 0
			//OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	        char * pCharToWrite = (char *)malloc(sizeof(char) * count);
	        for(int i = 0; i < count; i++)
	        {
	            *(char *)(pCharToWrite + i) = *(U1 *)(pBool + i);
	        }
	        
	        writeData(pCharToWrite, sizeof(char), count);
	        
	        free(pCharToWrite);
	#	else
	        writeData(pBool, sizeof(U1), count);
	#	endif
	
	    }
	    
	    //---------------------------------------------------------------------
	    void Parse::writeData(const void* const buf, UInt size, UInt count)
	    {
	        fwrite((void* const)buf, size, count, mpfFile);
	    }
	    //---------------------------------------------------------------------
	    void Parse::writeString(const AString& string)
	    {
	        fputs(string.c_str(), mpfFile);
	        // Write terminating newline char
	        fputc('\n', mpfFile);
	    }
	    //---------------------------------------------------------------------
	    void Parse::readFileHeader(DataStreamPtr& stream)
	    {
	        unsigned short headerID;
	        
	        // Read header ID
	        readShorts(stream, &headerID, 1);
	        
	        if (headerID == HEADER_STREAM_ID)
	        {
	            // Read version
	            AString ver = readString(stream);
	            if (ver != mVersion)
	            {
	                OGRE_EXCEPT(0, 
	                    "Invalid file: version incompatible, file reports " + AString(ver) +
	                    " Parse is version " + mVersion,
	                    "Parse::readFileHeader");
	            }
	        }
	        else
	        {
	            OGRE_EXCEPT(0, "Invalid file: no header", 
	                "Parse::readFileHeader");
	        }
	
	    }
	    //---------------------------------------------------------------------
	    unsigned short Parse::readChunk(DataStreamPtr& stream)
	    {
	        unsigned short id;
	        readShorts(stream, &id, 1);
	        
	        readInts(stream, &mCurrentstreamLen, 1);
	        return id;
	    }
	    //---------------------------------------------------------------------
	    void Parse::readBools(DataStreamPtr& stream, U1* pDest, UInt count)
	    {
	        //XXX Nasty Hack to convert 1 byte bools to 4 byte bools
	#	if 0
			//OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	        char * pTemp = (char *)malloc(1*count); // to hold 1-byte bools
	        stream->read(pTemp, 1 * count);
	        for(int i = 0; i < count; i++)
	            *(U1 *)(pDest + i) = *(char *)(pTemp + i);
	            
	        free (pTemp);
	#	else
	        stream->read(pDest, sizeof(U1) * count);
	#	endif
	        //no flipping on 1-byte datatypes
	    }
	    //---------------------------------------------------------------------
	    void Parse::readFloats(DataStreamPtr& stream, Real* pDest, UInt count)
	    {
	        stream->read(pDest, sizeof(Real) * count);
	        flipFromLittleEndian(pDest, sizeof(Real), count);
	    }
	    //---------------------------------------------------------------------
	    void Parse::readFloats(DataStreamPtr& stream, double* pDest, UInt count)
	    {
			// Read from Real, convert to double
			Real* tmp = OGRE_ALLOC_T(Real, count, MEMCATEGORY_GENERAL);
			Real* ptmp = tmp;
	        stream->read(tmp, sizeof(Real) * count);
	        flipFromLittleEndian(tmp, sizeof(Real), count);
			// Convert to doubles (no cast required)
			while(count--)
			{
				*pDest++ = *ptmp++;
			}
			OGRE_FREE(tmp, MEMCATEGORY_GENERAL);
	    }
	    //---------------------------------------------------------------------
	    void Parse::readShorts(DataStreamPtr& stream, unsigned short* pDest, UInt count)
	    {
	        stream->read(pDest, sizeof(unsigned short) * count);
	        flipFromLittleEndian(pDest, sizeof(unsigned short), count);
	    }
	    //---------------------------------------------------------------------
	    void Parse::readInts(DataStreamPtr& stream, unsigned int* pDest, UInt count)
	    {
	        stream->read(pDest, sizeof(unsigned int) * count);
	        flipFromLittleEndian(pDest, sizeof(unsigned int), count);
	    }
	    //---------------------------------------------------------------------
	    AString Parse::readString(DataStreamPtr& stream, UInt numChars)
	    {
	        assert (numChars <= 255);
	        char str[255];
	        stream->read(str, numChars);
	        str[numChars] = '\0';
	        return str;
	    }
	    //---------------------------------------------------------------------
	    AString Parse::readString(DataStreamPtr& stream)
	    {
	        return stream->getLine(false);
	    }
	    //---------------------------------------------------------------------
	    void Parse::writeObject(const Float3& vec)
	    {
	        writeFloats(&vec.x, 3);
	    }
	    //---------------------------------------------------------------------
	    void Parse::writeObject(const Float4& q)
	    {
	        Real tmp[4] = { q.x, q.y, q.z, q.w };
	        writeFloats(tmp, 4);
	    }
	    //---------------------------------------------------------------------
	    void Parse::readObject(DataStreamPtr& stream, Float3& pDest)
	    {
	        readFloats(stream, &pDest.x, 3);
	    }
	    //---------------------------------------------------------------------
	    void Parse::readObject(DataStreamPtr& stream, Float4& pDest)
	    {
	        Real tmp[4];
	        readFloats(stream, tmp, 4);
	        pDest.x = tmp[0];
	        pDest.y = tmp[1];
	        pDest.z = tmp[2];
	        pDest.w = tmp[3];
	    }
	    //---------------------------------------------------------------------
	
	
	    void Parse::flipToLittleEndian(void* pData, UInt size, UInt count)
	    {
			if(mFlipEndian)
			{
		        flipEndian(pData, size, count);
			}
	    }
	    
	    void Parse::flipFromLittleEndian(void* pData, UInt size, UInt count)
	    {
			if(mFlipEndian)
			{
		        flipEndian(pData, size, count);
			}
	    }
	    
	    void Parse::flipEndian(void * pData, UInt size, UInt count)
	    {
	        for(unsigned int index = 0; index < count; index++)
	        {
	            flipEndian((void *)((long)pData + (index * size)), size);
	        }
	    }
	    
	    void Parse::flipEndian(void * pData, UInt size)
	    {
	        char swapByte;
	        for(unsigned int byteIndex = 0; byteIndex < size/2; byteIndex++)
	        {
	            swapByte = *(char *)((long)pData + byteIndex);
	            *(char *)((long)pData + byteIndex) = *(char *)((long)pData + size - byteIndex - 1);
	            *(char *)((long)pData + size - byteIndex - 1) = swapByte;
	        }
	    }
	    
	}
	
};
