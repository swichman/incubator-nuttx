/****************************************************************************
 * arch/xtensa/src/common/xtensa_hostfs.c
 *
 *   Copyright (C) 2018 Pinecone Inc. All rights reserved.
 *   Author: Xiang Xiao <xiaoxiang@pinecone.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/fs/hostfs.h>

#include <arch/simcall.h>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int host_call(int nr, int param1, int param2, int param3)
{
  int ret;
  int err;

  ret = simcall(nr, param1, param2, param3, &err);
  if (ret < 0)
    {
      ret = -err;
    }

  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int host_open(const char *pathname, int flags, int mode)
{
  int simcall_flags = 0;

  switch ((flags & O_ACCMODE))
    {
      case O_RDONLY:
        simcall_flags = SIMCALL_O_RDONLY;
        break;
      case O_WRONLY:
        simcall_flags = SIMCALL_O_WRONLY;
        break;
      case O_RDWR:
        simcall_flags = SIMCALL_O_RDWR;
        break;
    }

  if ((flags & O_APPEND) != 0)
    {
      simcall_flags |= SIMCALL_O_APPEND;
    }

  if ((flags & O_TRUNC) != 0)
    {
      simcall_flags |= SIMCALL_O_TRUNC;
    }

  if ((flags & O_CREAT) != 0)
    {
      simcall_flags |= SIMCALL_O_CREAT;
    }

  if ((flags & O_EXCL) != 0)
    {
      simcall_flags |= SIMCALL_O_EXCL;
    }

  return host_call(SIMCALL_SYS_OPEN, (int)pathname, simcall_flags, mode);
}

int host_close(int fd)
{
  return host_call(SIMCALL_SYS_CLOSE, fd, 0, 0);
}

ssize_t host_read(int fd, void *buf, size_t count)
{
  return host_call(SIMCALL_SYS_READ, fd, (int)buf, count);
}

ssize_t host_write(int fd, const void *buf, size_t count)
{
  return host_call(SIMCALL_SYS_WRITE, fd, (int)buf, count);
}

off_t host_lseek(int fd, off_t offset, int whence)
{
  return host_call(SIMCALL_SYS_LSEEK, fd, offset, whence);
}

int host_ioctl(int fd, int request, unsigned long arg)
{
  return -ENOSYS;
}

void host_sync(int fd)
{
}

int host_dup(int fd)
{
  return -ENOSYS;
}

int host_fstat(int fd, struct stat *buf)
{
  /* XXX determine the size using lseek? */

  memset(buf, 0, sizeof(*buf));
  buf->st_mode = S_IFREG | 0777;
  return 0;
}

int host_ftruncate(int fd, off_t length)
{
  return -ENOSYS;
}

void *host_opendir(const char *name)
{
  return NULL;
}

int host_readdir(void *dirp, struct dirent *entry)
{
  return -ENOSYS;
}

void host_rewinddir(void *dirp)
{
}

int host_closedir(void *dirp)
{
  return -ENOSYS;
}

int host_statfs(const char *path, struct statfs *buf)
{
  return 0;
}

int host_unlink(const char *pathname)
{
  return -ENOSYS;
}

int host_mkdir(const char *pathname, mode_t mode)
{
  return -ENOSYS;
}

int host_rmdir(const char *pathname)
{
  return host_unlink(pathname);
}

int host_rename(const char *oldpath, const char *newpath)
{
  return -ENOSYS;
}

int host_stat(const char *path, struct stat *buf)
{
  int ret = host_open(path, O_RDONLY, 0);
  if (ret >= 0)
    {
      int fd = ret;
      ret = host_fstat(fd, buf);
      host_close(fd);
    }

  if (ret < 0)
    {
      /* Since semihosting doesn't support directory yet,
       * we have to assume it's a directory here.
       */

      ret = 0;
      memset(buf, 0, sizeof(*buf));
      buf->st_mode = S_IFDIR | 0777;
    }

  return ret;
}