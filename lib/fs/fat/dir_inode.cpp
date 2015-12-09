#include "fat/dir_inode.hpp"
#include "fat/dir.hpp"
#include <ecl/iostream.hpp>

using namespace fat;

dir_inode::dir_inode(FATFS *fs, const allocator &alloc, const char *path, const char *name)
    :m_alloc(alloc)
    ,m_path()
    ,m_fs(fs)
    ,my_ptr(nullptr)
{
    if (!path && !name) {
        m_path = allocate_path("/", nullptr, m_alloc);
    } else {
        m_path = allocate_path(path, name, m_alloc);
    }
}

dir_inode::~dir_inode()
{
}

dir_inode::type dir_inode::get_type() const
{
    return dir_inode::type::dir;
}

fs::dir_ptr dir_inode::open_dir()
{

    assert(!my_ptr.expired());
    DIR fat_dir;

    FRESULT res = pf_opendir(m_fs, &fat_dir, m_path->get_path());
    // TODO: graceful error handing
    assert(res == FR_OK);

    auto inode = my_ptr.lock();
    assert(inode);

    auto ptr = ecl::allocate_shared< dir, decltype(m_alloc) >
            (m_alloc, inode, m_fs, m_alloc, fat_dir, m_path);

    return ptr;
}

ssize_t dir_inode::size() const
{
    // TODO
    return -1;
}

ssize_t dir_inode::get_name(char *buf, size_t buf_sz) const
{
    assert(buf);
    assert(buf_sz);

    const char *path = m_path->get_path();

    size_t path_len = strlen(path);
    const char *start = path;
    const char *end;

    assert(path[path_len - 1] == '/');
    end = path + path_len;

    // Skip trailing '/'
    for (uint i = path_len - 1; i > 0; --i) {
        if (path[i - 1] == '/') {
            start = path + i - 1; // Assuming that 'i' is an index of the array
            break;
        }
    }

    // Reserve place for null terminator
    size_t to_copy = std::min(buf_sz - 1, (size_t) (end - start));

    // Algorithm check
    assert(to_copy < buf_sz);
    assert(start < end);

    buf[to_copy] = 0;

    std::copy(start, end, buf);

    return path_len;
}

int dir_inode::set_weak(const fs::inode_ptr &ptr)
{
    assert(my_ptr.expired());
    assert(ptr);
    my_ptr = ptr;
    return 0;
}
