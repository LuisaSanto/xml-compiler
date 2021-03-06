#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; } 

//---------------------------------------------------------------------------

void xpl::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC; 
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

inline void xpl::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void xpl::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of binary expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void xpl::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  std::shared_ptr<xpl::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    node->type(symbol->type());
  }
  else {
    throw id;
  }
}

void xpl::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void xpl::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  /*ASSERT_UNSPEC;

  try {
    node->lvalue()->accept(this, lvl);
  } catch (const std::string &id) {
    std::shared_ptr<xpl::symbol> symbol = std::make_shared<xpl::symbol>(new basic_type(4, basic_type::TYPE_INT), id, 0);
    _symtab.insert(id, symbol);
    _parent->set_new_symbol(symbol);  // advise parent that a symbol has been inserted
    node->lvalue()->accept(this, lvl);  //DAVID: bah!
  }

  if (node->lvalue()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of assignment expression");

  node->rvalue()->accept(this, lvl + 2);
  if (node->rvalue()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of assignment expression");

  // in XPL, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));*/
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_evaluation_node(xpl::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void xpl::type_checker::do_print_node(xpl::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_read_node(xpl::read_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->accept(this, lvl + 2);
  node->type(new basic_type(4, basic_type::TYPE_UNSPEC));
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_while_node(xpl::while_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void xpl::type_checker::do_if_node(xpl::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void xpl::type_checker::do_if_else_node(xpl::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void xpl::type_checker::do_block_node(xpl::block_node * const node, int lvl){
  //nothing to be done probably
}

void xpl::type_checker::do_next_node(xpl::next_node * const node, int lvl){
  //nothing to be done probably
}

void xpl::type_checker::do_stop_node(xpl::stop_node * const node, int lvl){
  //also nothing to be done probably
}

void xpl::type_checker::do_sweep_up_node(xpl::sweep_up_node * const node, int lvl){
  if(node->lval())  node->lval()->accept(this, lvl + 4);
  if(node->init())  node->init()->accept(this, lvl + 4);
  if(node->cond())  node->cond()->accept(this, lvl + 4);
  if(node->after()) node->after()->accept(this, lvl + 4);
}

void xpl::type_checker::do_sweep_down_node(xpl::sweep_down_node * const node, int lvl){
  if(node->lval())  node->lval()->accept(this, lvl + 4);
  if(node->init())  node->init()->accept(this, lvl + 4);
  if(node->cond())  node->cond()->accept(this, lvl + 4);
  if(node->after()) node->after()->accept(this, lvl + 4);
}

void xpl::type_checker::do_fun_call_node(xpl::fun_call_node * const node, int lvl){
    ASSERT_UNSPEC; 
    std::shared_ptr<xpl::symbol> sym = _symtab.find(*node->name());

    std::cout << "type checker funcall - initializing arguments" << std::endl;
    if (node->arguments() != nullptr) node->arguments()->accept(this, lvl);
    
    if(sym == nullptr) {
        throw sym->name() + " undeclared";
    }
    node->type(new basic_type(sym->type()->size(), sym->type()->name()));

}

void xpl::type_checker::do_fun_decl_node(xpl::fun_decl_node * const node, int lvl){
  const std::string &id = *node->identifier();
  if (!_symtab.insert(id, std::make_shared<xpl::symbol>(node->type(), id, 0, node->scope()))) {
     std::shared_ptr<xpl::symbol> sym = _symtab.find(id);
     if (sym->scope() == XPL_EXTERN) {
      _symtab.replace(id, std::make_shared<xpl::symbol>(node->type(), id, 0, node->scope()));
     } else { 
        throw id + " redeclared";
     }
  } 
  std::shared_ptr<xpl::symbol> simba = _symtab.find(id);
  simba->args(node->args());
}

void xpl::type_checker::do_fun_def_node(xpl::fun_def_node * const node, int lvl){
  if (node->retval() != nullptr) node->retval()->accept(this, lvl);
}
void xpl::type_checker::do_identity_node(xpl::identity_node * const node, int lvl){
  processUnaryExpression(node, lvl + 2); 
}

void xpl:: type_checker::do_index_node(xpl::index_node * const node, int lvl){
  node->base()->accept(this, lvl + 2);
  if (node->base()->type()->name() != basic_type::TYPE_POINTER)
    throw "attempting to get the index of a non-pointer argument";
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void xpl::type_checker::do_memory_alloc_node(xpl::memory_alloc_node * const node, int lvl){
  ASSERT_UNSPEC;
 
  node->arg()->accept(this, lvl + 2);
  if (node->arg()->type()->name() == basic_type::TYPE_UNSPEC) // transforming into int
    node->arg()->type(new basic_type(4, basic_type::TYPE_INT));

  if (node->arg()->type()->name() != basic_type::TYPE_INT)
    throw "cannot allocate memory with a non-integer argument";
}

void xpl::type_checker::do_pos_indication_node(xpl::pos_indication_node * const node, int lvl){
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->label() != "lvalue_node" || node->argument()->label() != "identifier_node" ||
      node->argument()->label() != "index_node") 
    throw "cannot indicate position of non-lvalue arguments"; //label = name. this node extends unaryexpression extends expression extends basic node it has names or labels 
}
 
void xpl::type_checker::do_print_line_node(xpl::print_line_node * const node, int lvl){
  node->argument()->accept(this, lvl + 2);

  if (node->argument()->type()->name() == basic_type::TYPE_POINTER)
    throw "cannot print pointer";
  if(node->argument()->type()->name() == basic_type::TYPE_UNSPEC)
    node->argument()->type(new basic_type(4, basic_type::TYPE_INT));
}

void xpl::type_checker::do_return_node(xpl::return_node * const node, int lvl){
  node->accept(this, lvl + 2);
}

void xpl::type_checker::do_null_node(xpl::null_node * const node, int lvl){
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_POINTER));
}

void xpl::type_checker::do_variable_node(xpl::variable_node * const node, int lvl){
  const std::string &id = *node->identifier();
 
  if (!_symtab.insert(id, std::make_shared<xpl::symbol>(node->type(), id, 0, node->scope()))) { 
     std::shared_ptr<xpl::symbol> sym = _symtab.find(id);
     if (sym->scope() == XPL_EXTERN) {
      _symtab.replace(id, std::make_shared<xpl::symbol>(node->type(), id, 0, node->scope()));
     } else { 
        throw id + " redeclared";
     }
  }
   
  if (node->initializer() != nullptr) {
     node->initializer()->accept(this, lvl+2);
     if (node->type()->name() == node->initializer()->type()->name())
        return;
     else if (node->type()->name() == basic_type::TYPE_DOUBLE
        && node->initializer()->type()->name() == basic_type::TYPE_INT)
  return;
     else 
  throw std::string("wrong type for initializer");
  }
  
}



