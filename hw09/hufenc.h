/*created by: Douglas von Kohorn
PS9
*/
#ifndef HUFENC_H
#define HUFENC_H

static int comp(void* p, void* q);
void print_element(const void* node, void* clientData);
void writeCodetree(Codetree ctree, Obitstream obs);
static Bitstring walkTree(Walker scan, Bitstring path);

#endif
