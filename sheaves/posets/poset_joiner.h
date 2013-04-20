
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class POSET_JOINER

#ifndef POSET_JOINER_H
#define POSET_JOINER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

namespace sheaf
{

class abstract_poset_member;
class tern;
class poset_state_handle;
class scoped_index;
class subposet;

///
/// Computes the join of given poset members.
///
class SHEAF_DLL_SPEC poset_joiner
{
public:

  ///
  /// Creates a joiner for poset xhost.
  ///
  poset_joiner(const poset_state_handle* xhost);

  ///
  /// Destructor; not virtual, can not be base class.
  ///
  ~poset_joiner();

  ///
  /// The join of the members of xexpansion
  ///
  void join(const scoped_index* xexpansion,
	    int xexpansion_ct,
	    const tern& xgreatest,
	    abstract_poset_member& xresult);

  ///
  /// The join of the members of xexpansion
  ///
  void join(subposet* xexpansion,
	    const tern& xgreatest,
	    abstract_poset_member& xresult);

  ///
  /// The host poset.
  ///
  poset_state_handle* host() const;

private:

  ///
  /// The host poset.
  ///
  poset_state_handle* _host;
};
 

} // namespace sheaf

#endif // ifndef POSET_JOINER_H
