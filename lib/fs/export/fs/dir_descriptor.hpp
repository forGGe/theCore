/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef LIB_FS_DIR_DESCRIPTOR_HPP_
#define LIB_FS_DIR_DESCRIPTOR_HPP_


#include <ecl/memory.hpp>
#include "types.hpp"

namespace fs
{

class dir_descriptor
{
public:
    dir_descriptor(const inode_weak &node);
    virtual ~dir_descriptor();


	// Next entity in a dir
	// nullptr returned if no more items
    virtual inode_ptr next() = 0;
	// Rewinds to the start of the dir
	// -1 if error, 0 otherwise
	virtual int rewind() = 0;
    // Closes a descriptor
    virtual int close() = 0;

protected:
    // Associated inode
    inode_ptr m_inode;
};

}

#endif
