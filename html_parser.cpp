#include "html_parser.h"

int main(int argc, char **argv) {
  int i;
  FILE *html_handle;
  char *html_doc;
  uint32_t html_doc_size;

  html_handle = fopen(argv[1], "r");
  //html_doc_size = lseek(html_handle, 0, SEEK_END);
  fseek(html_handle, 0L, SEEK_END);
  html_doc_size = ftell(html_handle);
  fseek(html_handle, 0L, SEEK_SET);
  
  fprintf(stderr, "[*] DOC SIZE: %d\n", html_doc_size);

  html_doc = malloc(sizeof(char) * (html_doc_size + 1));
  fprintf(stderr, "[*] start reading into: %x\n", html_doc);
  
  fgets(html_doc, html_doc_size, html_handle);
  
  //for(i=0; i < html_doc_size; i++){
    //fprintf(stderr, "[*] %s\n", (char)fgetc(html_handle));
    //fgets(html_doc, html_doc_size, html_handle);
    //html_doc[i] = fgetc(html_handle);
    //fprintf(stderr, "[*] html_doc[%d]: %s", i, &html_doc[i]);
  //}

  uint32_t html_doc_index = 0;
  for(i=0; i<html_doc_size-1; i++){
    char *cur_char = (html_doc + (i * sizeof(char)));
    fprintf(stderr, "[*] parse loop cur_char: %s\n", cur_char); 
    if(*cur_char == '<') {
      fprintf(stderr, "[*] we got a <\n");
      parse_node(html_doc, 
        &html_doc_index, 
        html_doc_size, 0);
      i += html_doc_index;
    }
  }
  return 0;
}

int parse_node(char *html, uint32_t *html_doc_index,
  uint32_t doc_size, dom_node_t *parent) {
  fprintf(stderr, "[*] parse_node called\n");
  fprintf(stderr, "[*] html_doc_index=%d\n", *html_doc_index);
  if(*html_doc_index >= doc_size)
    return 0;

  dom_node_t *cur_node = NULL;

  do {
    //append context to node name
    *html_doc_index += 1;
    fprintf(stderr, "waiting for >, html_doc_index: %d\n", *html_doc_index);
  } while(*(html +*html_doc_index) != '>');
  //create HTML node and update
  //cur_node = new(tag_name, parent);
  fprintf(stderr, "create new node\n");

  do {
    //read body of the tag
    *html_doc_index += 1;
  } while(*(html + *html_doc_index) != '<');
  
  if(*(html + (*html_doc_index+1)) == '/') {
    //end of current tag
    do {
      *html_doc_index += 1;
    } while(*(html + *html_doc_index) != '>');
    return 0;
  }
  else{
    fprintf(stderr, "[*] html_doc_index: %d, doc_size: %d\n", *html_doc_index, doc_size);
    parse_node(html, html_doc_index, doc_size, cur_node);
  }
  return 0;
}
