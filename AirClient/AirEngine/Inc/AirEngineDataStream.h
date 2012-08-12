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
#ifndef ENGINEDATASTREAM_HEAD_FILE
#define ENGINEDATASTREAM_HEAD_FILE

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirCommonRefPtr.h"
namespace Air{
	
	
	namespace Client {
	#define SharedPtr		Common::RefPtr
	
		/** General purpose class used for encapsulating the reading of data.
		@remarks
			This class performs basically the same tasks as std::basic_istream, 
			except that it does not have any formatting capabilities, and is
			designed to be subclassed to receive data from multiple sources,
			including libraries which have no compatibility with the STL's
			stream interfaces. As such, this is an abstraction of a set of 
			wrapper classes which pretend to be standard stream classes but 
			can actually be implemented quite differently. 
		@par
			Generally, if a plugin or application provides an ArchiveFactory, 
			it should also provide a DataStream subclass which will be used
			to stream data out of that Archive implementation, unless it can 
			use one of the common implementations included.
		@note
			Ogre makes no guarantees about thread safety, for performance reasons.
			If you wish to access stream data asynchronously then you should
			organise your own mutexes to avoid race conditions. 
		*/
		class ENGINE_EXPORT DataStream //: public StreamAlloc
		{
		protected:
			/// The name (e.g. resource name) that can be used to identify the source fot his data (optional)
			AString mName;		
	        /// Size of the data in the stream (may be 0 if size cannot be determined)
	        UInt mSize;
	        #define OGRE_STREAM_TEMP_SIZE 128
		public:
			/// Constructor for creating unnamed streams
	        DataStream() : mSize(0) {}
			/// Constructor for creating named streams
			DataStream(const AString& name) : mName(name), mSize(0) {}
			/// Returns the name of the stream, if it has one.
			const AString& getName(void) { return mName; }
	        virtual ~DataStream() {}
			// Streaming operators
	        template<typename T> DataStream& operator>>(T& val);
			/** Read the requisite number of bytes from the stream, 
				stopping at the end of the file.
			@param buf Reference to a buffer pointer
			@param count Number of bytes to read
			@returns The number of bytes read
			*/
			virtual UInt read(void* buf, UInt count) = 0;
			/** Get a single line from the stream.
			@remarks
				The delimiter character is not included in the data
				returned, and it is skipped over so the next read will occur
				after it. The buffer contents will include a
				terminating character.
	        @note
	            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
	            otherwise, it'll produce unexpected results.
			@param buf Reference to a buffer pointer
			@param maxCount The maximum length of data to be read, excluding the terminating character
			@param delim The delimiter to stop at
			@returns The number of bytes read, excluding the terminating character
			*/
			virtual UInt readLine(char* buf, UInt maxCount, const AString& delim = "\n");
			
		    /** Returns a AString containing the next line of data, optionally 
			    trimmed for whitespace. 
		    @remarks
			    This is a convenience method for text streams only, allowing you to 
			    retrieve a AString object containing the next line of data. The data
			    is read up to the next newline character and the result trimmed if
			    required.
	        @note
	            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
	            otherwise, it'll produce unexpected results.
		    @param 
			    trimAfter If true, the line is trimmed for whitespace (as in 
			    AString.trim(true,true))
		    */
		    virtual AString getLine( U1 trimAfter = true );
	
		    /** Returns a AString containing the entire stream. 
		    @remarks
			    This is a convenience method for text streams only, allowing you to 
			    retrieve a AString object containing all the data in the stream.
		    */
		    virtual AString getAsString(void);
	
			/** Skip a single line from the stream.
	        @note
	            If you used this function, you <b>must</b> open the stream in <b>binary mode</b>,
	            otherwise, it'll produce unexpected results.
			@param delim The delimiter(s) to stop at
			@returns The number of bytes skipped
			*/
			virtual UInt skipLine(const AString& delim = "\n");
	
			/** Skip a defined number of bytes. This can also be a negative value, in which case
			the file pointer rewinds a defined number of bytes. */
			virtual void skip(long count) = 0;
		
			/** Repositions the read point to a specified byte.
		    */
		    virtual void seek( UInt pos ) = 0;
			
			/** Returns the current byte offset from beginning */
		    virtual UInt tell(void) const = 0;
	
			/** Returns true if the stream has reached the end.
		    */
		    virtual U1 eof(void) const = 0;
	
			/** Returns the total size of the data to be read from the stream, 
				or 0 if this is indeterminate for this stream. 
			*/
	        UInt size(void) const { return mSize; }
	
	        /** Close the stream; this makes further operations invalid. */
	        virtual void close(void) = 0;
			
	
		};
	
		/** Shared pointer to allow data streams to be passed around without
			worrying about deallocation
		*/
	 	typedef SharedPtr<DataStream> DataStreamPtr;
	// 
	// 	/// List of DataStream items
	 	typedef std::list<DataStreamPtr> DataStreamList;
	// 	/// Shared pointer to list of DataStream items
	 	typedef SharedPtr<DataStreamList> DataStreamListPtr;
	
		/** Common subclass of DataStream for handling data from chunks of memory.
		*/
		class ENGINE_EXPORT MemoryDataStream : public DataStream
		{
		protected:
	        /// Pointer to the start of the data area
		    U8* mData;
	        /// Pointer to the current position in the memory
		    U8* mPos;
	        /// Pointer to the end of the memory
		    U8* mEnd;
	        /// Do we delete the memory on close
			U1 mFreeOnClose;			
		public:
			
			/** Wrap an existing memory chunk in a stream.
			@param pMem Pointer to the existing memory
			@param size The size of the memory chunk in bytes
			@param freeOnClose If true, the memory associated will be destroyed
				when the stream is destroyed. Note: it's important that if you set
				this option to true, that you allocated the memory using OGRE_ALLOC_T
				with a category of MEMCATEGORY_GENERAL ensure the freeing of memory 
				matches up.
			*/
			MemoryDataStream(void* pMem, UInt size, U1 freeOnClose = false);
			
			/** Wrap an existing memory chunk in a named stream.
			@param name The name to give the stream
			@param pMem Pointer to the existing memory
			@param size The size of the memory chunk in bytes
			@param freeOnClose If true, the memory associated will be destroyed
				when the stream is destroyed. Note: it's important that if you set
				this option to true, that you allocated the memory using OGRE_ALLOC_T
				with a category of MEMCATEGORY_GENERAL ensure the freeing of memory 
				matches up.
			*/
			MemoryDataStream(const AString& name, void* pMem, UInt size, 
					U1 freeOnClose = false);
	
			/** Create a stream which pre-buffers the contents of another stream.
			@remarks
				This constructor can be used to intentionally read in the entire
				contents of another stream, copying them to the internal buffer
				and thus making them available in memory as a single unit.
			@param sourceStream Another DataStream which will provide the source
				of data
			@param freeOnClose If true, the memory associated will be destroyed
				when the stream is destroyed.
			*/
			MemoryDataStream(DataStream& sourceStream, 
					U1 freeOnClose = true);
			
			/** Create a stream which pre-buffers the contents of another stream.
			@remarks
				This constructor can be used to intentionally read in the entire
				contents of another stream, copying them to the internal buffer
				and thus making them available in memory as a single unit.
			@param sourceStream Weak reference to another DataStream which will provide the source
				of data
			@param freeOnClose If true, the memory associated will be destroyed
				when the stream is destroyed.
			*/
			MemoryDataStream(DataStreamPtr& sourceStream, 
					U1 freeOnClose = true);
	
			/** Create a named stream which pre-buffers the contents of 
				another stream.
			@remarks
				This constructor can be used to intentionally read in the entire
				contents of another stream, copying them to the internal buffer
				and thus making them available in memory as a single unit.
			@param name The name to give the stream
			@param sourceStream Another DataStream which will provide the source
				of data
			@param freeOnClose If true, the memory associated will be destroyed
				when the stream is destroyed.
			*/
			MemoryDataStream(const AString& name, DataStream& sourceStream, 
					U1 freeOnClose = true);
	
	        /** Create a named stream which pre-buffers the contents of 
	        another stream.
	        @remarks
	        This constructor can be used to intentionally read in the entire
	        contents of another stream, copying them to the internal buffer
	        and thus making them available in memory as a single unit.
	        @param name The name to give the stream
	        @param sourceStream Another DataStream which will provide the source
	        of data
	        @param freeOnClose If true, the memory associated will be destroyed
	        when the stream is destroyed.
	        */
	        MemoryDataStream(const AString& name, const DataStreamPtr& sourceStream, 
	            U1 freeOnClose = true);
	
	        /** Create a stream with a brand new empty memory chunk.
			@param size The size of the memory chunk to create in bytes
			@param freeOnClose If true, the memory associated will be destroyed
				when the stream is destroyed.
			*/
			MemoryDataStream(UInt size, U1 freeOnClose = true);
			/** Create a named stream with a brand new empty memory chunk.
			@param name The name to give the stream
			@param size The size of the memory chunk to create in bytes
			@param freeOnClose If true, the memory associated will be destroyed
				when the stream is destroyed.
			*/
			MemoryDataStream(const AString& name, UInt size, 
					U1 freeOnClose = true);
	
			~MemoryDataStream();
	
			/** Get a pointer to the start of the memory block this stream holds. */
			U8* getPtr(void) { return mData; }
			
			/** Get a pointer to the current position in the memory block this stream holds. */
			U8* getCurrentPtr(void) { return mPos; }
			
			/** @copydoc DataStream::read
			*/
			UInt read(void* buf, UInt count);
			/** @copydoc DataStream::readLine
			*/
			UInt readLine(char* buf, UInt maxCount, const AString& delim = "\n");
			
			/** @copydoc DataStream::skipLine
			*/
			UInt skipLine(const AString& delim = "\n");
	
			/** @copydoc DataStream::skip
			*/
			void skip(long count);
		
			/** @copydoc DataStream::seek
			*/
		    void seek( UInt pos );
			
			/** @copydoc DataStream::tell
			*/
		    UInt tell(void) const;
	
			/** @copydoc DataStream::eof
			*/
		    U1 eof(void) const;
	
	        /** @copydoc DataStream::close
	        */
	        void close(void);
	
			/** Sets whether or not to free the encapsulated memory on close. */
			void setFreeOnClose(U1 free) { mFreeOnClose = free; }
		};
	
	    /** Shared pointer to allow memory data streams to be passed around without
	    worrying about deallocation
	    */
	    typedef SharedPtr<MemoryDataStream> MemoryDataStreamPtr;
	
	    /** Common subclass of DataStream for handling data from 
			std::basic_istream.
		*/
		class ENGINE_EXPORT FileStreamDataStream : public DataStream
		{
		protected:
			/// Reference to source stream
			std::ifstream* mpStream;
	        U1 mFreeOnClose;			
		public:
			/** Construct stream from an STL stream
	        @param s Pointer to source stream
	        @param freeOnClose Whether to delete the underlying stream on 
	            destruction of this class
	        */
			FileStreamDataStream(std::ifstream* s, 
	            U1 freeOnClose = true);
			/** Construct named stream from an STL stream
	        @param name The name to give this stream
	        @param s Pointer to source stream
	        @param freeOnClose Whether to delete the underlying stream on 
	            destruction of this class
	        */
			FileStreamDataStream(const AString& name, 
	            std::ifstream* s, 
	            U1 freeOnClose = true);
	
			/** Construct named stream from an STL stream, and tell it the size
	        @remarks
	            This variant tells the class the size of the stream too, which 
	            means this class does not need to seek to the end of the stream 
	            to determine the size up-front. This can be beneficial if you have
	            metadata about the contents of the stream already.
	        @param name The name to give this stream
	        @param s Pointer to source stream
	        @param size Size of the stream contents in bytes
	        @param freeOnClose Whether to delete the underlying stream on 
	            destruction of this class. If you specify 'true' for this you
				must ensure that the stream was allocated using OGRE_NEW_T with 
				MEMCATEGRORY_GENERAL.
	        */
			FileStreamDataStream(const AString& name, 
	            std::ifstream* s, 
	            UInt size, 
	            U1 freeOnClose = true);
	
	        ~FileStreamDataStream();
	
			/** @copydoc DataStream::read
			*/
			UInt read(void* buf, UInt count);
			/** @copydoc DataStream::readLine
			*/
	        UInt readLine(char* buf, UInt maxCount, const AString& delim = "\n");
			
			/** @copydoc DataStream::skip
			*/
			void skip(long count);
		
			/** @copydoc DataStream::seek
			*/
		    void seek( UInt pos );
	
			/** @copydoc DataStream::tell
			*/
			UInt tell(void) const;
	
			/** @copydoc DataStream::eof
			*/
		    U1 eof(void) const;
	
	        /** @copydoc DataStream::close
	        */
	        void close(void);
			
			
		};
	
		/** Common subclass of DataStream for handling data from C-style file 
			handles.
	    @remarks
	        Use of this class is generally discouraged; if you want to wrap file
	        access in a DataStream, you should definitely be using the C++ friendly
	        FileStreamDataStream. However, since there are quite a few applications
	        and libraries still wedded to the old FILE handle access, this stream
	        wrapper provides some backwards compatibility.
		*/
		class ENGINE_EXPORT FileHandleDataStream : public DataStream
		{
		protected:
			FILE* mFileHandle;
		public:
			/// Create stream from a C file handle
			FileHandleDataStream(FILE* handle);
			/// Create named stream from a C file handle
			FileHandleDataStream(const AString& name, FILE* handle);
	        ~FileHandleDataStream();
	
			/** @copydoc DataStream::read
			*/
			UInt read(void* buf, UInt count);
	
			/** @copydoc DataStream::skip
			*/
			void skip(long count);
		
			/** @copydoc DataStream::seek
			*/
		    void seek( UInt pos );
	
			/** @copydoc DataStream::tell
			*/
			UInt tell(void) const;
	
			/** @copydoc DataStream::eof
			*/
		    U1 eof(void) const;
	
	        /** @copydoc DataStream::close
	        */
	        void close(void);
	
		};
	
	#define MEMCATEGORY_GENERAL	0
	#define OGRE_ALLOC_T(type,size,n)	new	type[size]
	#define OGRE_FREE(p,n)			delete[]	p
	#define OGRE_EXCEPT(m,n,o)			{};
	#define LogManager(str)				{};
	#define OGRE_DELETE_T(m,n,o)		delete m
	#define OGRE_NEW					new
		//::getSingleton().logMessage	
	}
};

#endif

