#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

void test_os_create_and_delete_file()
{
	char *file = "existentfile";
	char buf[256];

	/* open file for reading and writing, with owner read/write permissions */
	int mode = FAM_READ | FAM_WRITE;
	int perms = FAP_READ | FAP_WRITE;
	path_id path;
	error_code result = _os_create(file, mode, &path, perms);
	if (result == 0)
	{
		printf("%s [PASS] _os_create(\"%s\", %d, [%d], %x) = %d\n", __func__, file, mode, path, perms, result);
		int result = _os_close(path);
		if (result == 0)
		{
			int mode = FAM_READ;
			printf("%s [PASS] _os_close(%d) = %d\n", __func__, path, result);
			
			result = _os_delete(file, mode);
			if (result == 0)
			{
				printf("%s [PASS] _os_delete(\"%s\", %x) = %d\n", __func__, file, mode, result);
			}
			else
			{
				printf("%s [FAIL] _os_delete(\"%s\", %x) = %d\n", __func__, file, mode, result);
			}
		}
		else
		{
			printf("%s [FAIL] _os_close(%d) = %d\n", __func__, path, result);
		}
	}
	else
	{
		printf("%s [FAIL] _os_create(\"%s\", %d, [%d], %x) = %d\n", __func__, file, mode, path, perms, result);
	}
}

void test_os_open_nonexistent_file()
{
	char *file = "nonexistentfile";

	int mode = FAM_READ;
	path_id path;
	int result = _os_open(file, mode, &path);
	if (result != 0)
	{
		printf("%s [PASS] _os_open(\"%s\", %x, [%d]) = %d\n", __func__, file, mode, path, result);
	}
	else
	{
		printf("%s [FAIL] _os_open(\"%s\", %x, [%d]) = %d\n", __func__, file, mode, path, result);
	}
}

void test_os_delete_nonexistent_file()
{
	char *file = "deletenonexistentfile";
	int mode = FAM_READ;
	
	int result = _os_delete(file, mode);
	if (result != 0)
	{
		printf("%s [PASS] _os_delete(\"%s\", %x) = %d\n", __func__, file, mode, result);
	}
	else
	{
		printf("%s [FAIL] _os_delete(\"%s\", %x) = %d\n", __func__, file, mode, result);
	}
}

/* test creation of a small file and seeking from various directions (start, current, end)
   coverage of this test is currently weak. A good test would be to add a large content file
   and seek within that.
   */
void test_os_create_and_seek()
{
	char *file = "text.txt";

	// delete the file if it exists, we don't care if we error here
	_os_delete(file, FAM_READ);

	/* open file for reading and writing, with owner read/write permissions */
	int mode = FAM_READ | FAM_WRITE;
	int perms = FAP_READ | FAP_WRITE;
	path_id path;
	int result = _os_create(file, mode, &path, perms);
	if (result == 0)
	{
		printf("%s [PASS] _os_create(\"%s\", %x, [%d], %d) = %d\n", __func__, file, mode, path, perms, result);
		char *message = "this is a line of text\n";
		int length = strlen(message);
		result = _os_writeln(path, message, &length);
		if (result == 0 && length == strlen(message))
		{
			printf("%s [PASS] _os_writeln(%d, \"%s\", [%d]) = %d\n", __func__, path, message, length, result);
			long offset = 5;
			int result = _os_seek(path, offset);
			if (result == 0)
			{
				// file position is now at 5
				char buf[32];
				int readsize = 2;
				
				printf("%s [PASS] _os_seek(%d, %ld) = %d\n", __func__, path, offset, result);
				result = _os_read(path, buf, &readsize);
				if (2 == readsize && buf[0] == 'i' && buf[1] == 's')
				{
					// file position is now at 5 + 2 = 7
					printf("%s [PASS] _os_read(%d, \"is\", [%d]) = %d\n", __func__, path, readsize, result);
				}
				else
				{
					printf("%s [FAIL] _os_read(%d, \"-\", [%d]) = %d\n", __func__, path, readsize, result);
				}
			}
			else
			{
				printf("%s [FAIL] _os_seek(%d, %ld) = %d\n", __func__, path, offset, result);
			}
			_os_close(path);
			_os_delete(file, FAM_READ);
		}
		else
		{
			printf("%s [FAIL] _os_writeln(%d, \"%s\", [%d]) = %d\n", __func__, path, message, length, result);
		}
	}
	else
	{
		printf("%s [FAIL] _os_create(\"%s\", %x, [%d], %d) = %d\n", __func__, file, mode, path, perms, result);
	}
}

void test_os_make_directory()
{
	char *file = "newdirectory";

	int perm = FAP_READ | FAP_WRITE | FAP_EXEC | FAP_PREAD | FAP_PWRITE | FAP_PEXEC;
	int result = _os_makdir(file, perm);
	if (result == 0)
	{
		printf("%s [PASS] _os_makdir(\"%s\", %d) = %d\n", __func__, file, perm, result);
		perm = FAP_READ | FAP_WRITE | FAP_PREAD | FAP_PWRITE;
		int result = _os_ss_attr(file, perm);
		if (result == 0)
		{
			printf("%s [PASS] _os_ss_attr(\"%s\", %d) = %d\n", __func__, file, perm, result);
			int mode = FAM_READ;
			result = _os_delete(file, mode);
			if (result == 0)
			{
    			printf("%s [PASS] _os_delete(\"%s\", %d) = %d\n", __func__, file, mode, result);
			}
			else
			{
    			printf("%s [FAIL] _os_delete(\"%s\", %d) = %d\n", __func__, file, mode, result);
			}
		}
		else
		{
			printf("%s [FAIL] _os_ss_attr(\"%s\", %d) = %d\n", __func__, file, perm, result);
		}
	}
	else
	{
		printf("%s [FAIL] _os_makdir(\"%s\", %d) = %d\n", __func__, file, perm, result);
	}
}

void test_os_make_and_attr_file()
{
	char *file = "newfile";

	int mode = FAM_READ | FAM_WRITE;
	int perm = FAP_READ | FAP_WRITE;
	path_id path;
	int result = _os_create(file, mode, &path, perm);
	if (result == 0)
	{
		printf("%s [PASS] _os_create(\"%s\", %x, [%d], %d) = %d\n", __func__, file, mode, path, perm, result);
		_os_close(path);
		perm = FAP_READ | FAP_WRITE | FAP_PREAD | FAP_PWRITE;
		int result = _os_ss_attr(file, perm);
		if (result == 0)
		{
			printf("%s [PASS] _os_ss_attr(\"%s\", %d) = %d\n", __func__, file, perm, result);
			int mode = FAM_READ;
			result = _os_delete(file, mode);
			if (result == 0)
			{
    			printf("%s [PASS] _os_delete(\"%s\", %d) = %d\n", __func__, file, mode, result);
			}
			else
			{
    			printf("%s [FAIL] _os_delete(\"%s\", %d) = %d\n", __func__, file, mode, result);
			}
		}
		else
		{
			printf("%s [FAIL] _os_ss_attr(\"%s\", %d) = %d\n", __func__, file, perm, result);
		}
	}
	else
	{
		printf("%s [FAIL] _os_create(\"%s\", %x, [%d], %d) = %d\n", __func__, file, mode, path, perm, result);
	}
}

int main()
{
	test_os_create_and_delete_file();
	test_os_open_nonexistent_file();
	test_os_delete_nonexistent_file();
	test_os_create_and_seek();
	test_os_make_directory();
	test_os_make_and_attr_file();

	return 0;
}
