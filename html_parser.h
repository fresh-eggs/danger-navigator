#include <stdio.h>
#include <stdint.h>
#include <string>
#include <vector>

//used for lseek, may not be windows compatible
#include <unistd.h>

//#ifndef HTML_PARSER_H
//#define HTML_PARSER_H

// nodes in the tree
// the DOM tree
// HTML node types

// parse each HTML char
  // determine the node type

using std::vector;
using std::string;


enum HTMLTypes {
  HTML,
  HEAD,
  BODY,
  P
};

struct html_element_t {
  string inner_html;
  HTMLTypes type;
};

struct dom_node_t {
  html_element_t *element;
  dom_node_t *parent;
  vector <dom_node_t *> children;
};

int parse_node(char *html, uint32_t *html_doc_index, 
  uint32_t doc_size, dom_node_t *parent);
