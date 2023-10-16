#ifndef _CODE_COMPRESS_H_
#define _CODE_COMPRESS_H_

NAME_SPACE_BEGIN

long Compress(void *in,long in_len,void *out);
long Decompress(void *in,long in_len,void*out);
long GetDecompressLength(void *in);

NAME_SPACE_END
#endif
