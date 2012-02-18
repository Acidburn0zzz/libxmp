#include "test.h"

int decrunch_pp(FILE *f, FILE *fo);


TEST(test_pp)
{
	FILE *f, *fo;
	int ret;
	struct stat st;

	f = fopen("data/mod.loving_is_easy.pp", "rb");
	fail_unless(f != NULL, "can't open data file");

	fo = fopen(TMP_FILE, "wb");
	fail_unless(fo != NULL, "can't open output file");

	ret = decrunch_pp(f, fo);
	fail_unless(ret == 0, "decompression fail");

	fclose(fo);
	fclose(f);

	f = fopen(TMP_FILE, "rb");
	fstat(fileno(f), &st);
	fail_unless(st.st_size == 49798, "decompression size error");

	ret = check_md5(TMP_FILE, "8919a05084ec684e52dd7bb1393e1089");
	fail_unless(ret == 0, "MD5 error");

	fclose(f);
}
END_TEST
