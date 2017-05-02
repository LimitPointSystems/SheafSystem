
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Interface for class poset_orderer.

#ifndef POSET_ORDERER_H
#define POSET_ORDERER_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef POSET_DFT_H
#include "SheafSystem/poset_dft.h"
#endif

#ifndef ZN_TO_BOOL_H
#include "SheafSystem/zn_to_bool.h"
#endif

namespace sheaf
{

class abstract_poset_member;
class subposet;
class poset_member;
  
///
/// Traverser to ensure validity of order relation.
///
class SHEAF_DLL_SPEC poset_orderer: public poset_dft
{
  // ===========================================================
  /// @name POSET_ORDERER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Constructor
  ///
  poset_orderer(poset_state_handle* xhost);

  ///
  /// Destructor
  ///
  ~poset_orderer();

  ///
  /// Make jrm order consistent with jim order
  ///
  void restore_order(subposet* xlower_bound = 0);

protected:

private:

  ///
  /// Lower bound for traversal;
  /// truncate descent when reach any member of this subposet
  ///
  subposet* _lower_bound;

  ///
  /// Determines if the member has been visited in the post order action.
  ///
  zn_to_bool* _post_visited;

  ///
  /// True, if the member at xindex has been visitied in the poset
  /// order action.
  ///
  bool has_been_post_visited(pod_index_type xindex) const
  {
    return ((*_post_visited)[xindex]);
  };

  //@}


  // ===========================================================
  /// @name POSET_DFT FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Previsit action for member, xmbr.
  ///
  void previsit_action(abstract_poset_member* xmbr);

  ///
  /// Link action for member, xmbr; disabled.
  ///
  inline void link_action(abstract_poset_member* xmbr,
                          abstract_poset_member* linked_mbr) {};

  ///
  /// Postvisit action for member, xmbr.
  ///
  void postvisit_action(abstract_poset_member* xmbr);

private:

  //@}


  // ===========================================================
  /// @name POSET_TRAVERSER FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Class invariant
  ///
  virtual bool  invariant() const;

protected:

private:

  //@}

};
  
} // namespace sheaf

#endif // ifndef POSET_ORDERER_H
