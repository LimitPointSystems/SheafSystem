// $RCSfile: poset_dft.h,v $ $Revision: 1.15 $ $Date: 2013/01/12 17:17:50 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class POSET_DFT

#ifndef POSET_DFT_H
#define POSET_DFT_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_TRAVERSER_H
#include "poset_traverser.h"
#endif

#ifndef STD_STACK_H
#include "std_stack.h"
#endif

namespace sheaf
{
  
class abstract_poset_member;

///
/// Abstract traverser (internal iterator) for poset which traverses
/// the cover relation graph in depth first order.
///
class SHEAF_DLL_SPEC poset_dft: public poset_traverser
{

public:

  // Class invariant same as base class

  // Constructors:

  ///
  /// Constructor
  ///
  poset_dft(const poset_state_handle* xhost);

  ///
  /// Destructor
  ///
  ~poset_dft();


protected:

  ///
  /// If true on return from previsit_action, descend into lower cover
  /// previsit_action can truncate dft by setting this false.
  ///
  bool _descend;

  ///
  /// Storage for abstract_poset_member objects, so we can reuse them,
  /// rather than creating one for each member in the graph.
  ///
  stack<abstract_poset_member*> _free_mbrs;

  // actions:

  void          private_traverse();
  void          recursive_dft(abstract_poset_member* xmbr);
  virtual void  previsit_action(abstract_poset_member* xmbr) = 0;
  virtual void  link_action(abstract_poset_member* xgreater, abstract_poset_member* xlesser) = 0;
  virtual void  postvisit_action(abstract_poset_member* xmbr) = 0;


};
 
} // namespace sheaf

#endif // ifndef POSET_DFT_H
