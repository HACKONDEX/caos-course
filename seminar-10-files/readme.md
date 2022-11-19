# FileSystem

### File types

1. __Regular__

2. __Directory__

3. __Symboliclink__

---

`touch` __-__ create file

`mkdir` __-__ create directory

`ln` __-__ create hard link

`ln -s` __-__ create symbolic link

---

### Stat functions

`stat`, `fstat`, `lstat`

```C
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int stat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *pathname, struct stat *buf);
```

##### struct stat

```C
#include <sys/stat.h>
#include <sys/types.h>


struct stat {
   dev_t     st_dev;         /* ID of device containing file */
   ino_t     st_ino;         /* inode number */
   mode_t    st_mode;        /* protection */
   nlink_t   st_nlink;       /* number of hard links */
   uid_t     st_uid;         /* user ID of owner */
   gid_t     st_gid;         /* group ID of owner */
   dev_t     st_rdev;        /* device ID (if special file) */
   off_t     st_size;        /* total size, in bytes */
   blksize_t st_blksize;     /* blocksize for filesystem I/O */
   blkcnt_t  st_blocks;      /* number of 512B blocks allocated */

   /* Since Linux 2.6, the kernel supports nanosecond
      precision for the following timestamp fields.
      For the details before Linux 2.6, see NOTES. */

   struct timespec st_atim;  /* time of last access */
   struct timespec st_mtim;  /* time of last modification */
   struct timespec st_ctim;  /* time of last status change */

#define st_atime st_atim.tv_sec      /* Backward compatibility */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
```

---

`st_mode` is a BitMask, it contains information about file type, permissions

* `S_IFSOCK 0140000 socket`

* `S_IFLNK 0120000 symbolic link`
  
* `S_IFREG 0100000 regular file`
  
* `S_IFBLK 0060000 block device`

* `S_IFDIR 0040000 directory`
  
* `S_IFCHR 0020000 character device`
  
* `S_IFIFO 0010000 FIFO`

To get those bits we should & the mask `S_IFMT == 0170000`

