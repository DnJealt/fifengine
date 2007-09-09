/***************************************************************************
 *   Copyright (C) 2005-2006 by the FIFE Team                              *
 *   fife-public@lists.sourceforge.net                                     *
 *   This file is part of FIFE.                                            *
 *                                                                         *
 *   FIFE is free software; you can redistribute it and/or modify          *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
 ***************************************************************************/

#ifndef FIFE_RENDERABLE_LOCATION_H
#define FIFE_RENDERABLE_LOCATION_H

// Standard C++ library includes
#include <string>

// 3rd party library includes

// FIFE includes
#include "renderable.h"

namespace FIFE {

	/** Contains information about the Location of a RenderAble.
	 *
	 *  This class is used to give RenderableProvider the information
	 *  where to find the data. 
	 *
	 *  Normally you could use it like this:
	 *  @code
	 *  // For an image or a static animation:
	 *  RenderableLocation location("somepicture.png");
	 *  ImageID = imageCachePtr->addImageFromLocation( location );
	 *
	 *  // To get a specific direction of an animation
	 *  RenderableLocation location("someanimation.frm");
	 *  location.setType( RenderAble::RT_ANIMATION );
	 *  location.setDirection( direction );
	 *  ImageID = imageCachePtr->addImageFromLocation( location );
	 *
	 *  @endcode
	 *
	 *  However for most static renderables you can write:
	 *  @code
	 *  ImageID = imageCachePtr->addImageFromFile( "somepicture.jpg" );
	 *  @endcode
	 *
	 *  @note: Currently only Files are implemented. Other stuff will follow.
	 */
	class RenderableLocation {

	public:
		typedef RenderAble::RenderableTypes LocationTypes;

		/** Constructor.
		 *
		 * @param type Location type.
		 * @param loc Name of the location.
		 */
		RenderableLocation( LocationTypes type = RenderAble::RT_UNDEFINED,
		  const std::string& loc = "");

		/** Creates RL_FILE from a single-image file.
		 *
		 * @param Path to image in VFS.
		 */
		RenderableLocation(const std::string & filename);
		
		/** Copy Constructor.
		 */
		RenderableLocation( const RenderableLocation& loc );

		/** Destructor.
		 */
		~RenderableLocation();

		/** Returns the filename.
		 *
		 * @return The filename.
		 */
		std::string getFilename() const { return m_string; };

		/** Sets the filename.
		 *
		 * @param filename The filename.
		 */
		void setFilename(const std::string& filename);

		/** Returns extension.
		 *
		 * @param The file extension.
		 */
		std::string getFileExtension() const;

		/** Returns a string representation.
		 * For Error Reporting.
		 *
		 * @return A string detailing the error.
		 */
		std::string toString() const;

		/** Returns the type of RenderableLocation.
		 *
		 * @return The type of RenderableLocation.
		 */
		LocationTypes getType() const { return m_type; }

		/** Set the type of RenderableLocation.
		 *
		 * @param type The type of RenderableLocation.
		 */
		void setType(LocationTypes type) { m_type = type; }

		/** Returns the frame of RenderableLocation.
		 *
		 * @return The frame of RenderableLocation.
		 */
		unsigned int  getFrame() const { return m_frame_idx; }

		/** Set the frame to read from a multi image format
		 *
		 *  @param frame The frame to read
		 */
		void setFrame(unsigned int frame) { m_frame_idx = frame; }

		/** Returns the direction of RenderableLocation.
		 *
		 * @return The direction of RenderableLocation.
		 */
		unsigned int  getDirection() const { return m_direction_idx; }

		/** Set the direction for the RenderableLocation
		 *
		 *  @param direction The direction to read from an .frm
		 */
		void setDirection(unsigned int direction) { m_direction_idx = direction; }


		/** Returns whether the RenderableLocation is valid.
		 *
		 *  A location is assumed valid. if it's filename is not ""
		 */
		bool isValid() const;

		/** Compares two RenderableLocations for equality.
		 */
		bool operator ==(const RenderableLocation& loc) const;

		/** Compares two RenderableLocations
		 * This is needed as the locations should be stored in a \c std::map
		 */
		bool operator <(const RenderableLocation& loc) const;

	private:
		// This is an implementation detail.
		// If direct vars hit the cache size too much,
		// we'll be using implicit sharing.
		LocationTypes m_type;
		std::string m_string;
		bool m_isValid;
		unsigned int m_frame_idx;
		unsigned int m_direction_idx;
	};

}; //FIFE
#endif
/* vim: set noexpandtab: set shiftwidth=2: set tabstop=2: */
