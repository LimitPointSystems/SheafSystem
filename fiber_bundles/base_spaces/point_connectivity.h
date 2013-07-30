

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Interface for class point_connectivity

#ifndef POINT_CONNECTIVITY_H
#define POINT_CONNECTIVITY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_CONNECTIVITY_H
#include "block_connectivity.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// Nodal connectivity for a block containing zones of type point.
/// Since a point block is just a collection of disconnected points, 
/// the "connectivity" list for each point contains just the point itself.
///
class SHEAF_DLL_SPEC point_connectivity : public block_connectivity
{
public:

 
  // ===========================================================
  /// @name POINT_CONNECTIVITY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor.
  /// Equivalent to point_connectivity(1)
  ///
  point_connectivity();

  ///
  /// Copy constructor
  ///
  point_connectivity(const point_connectivity& xother);

  ///
  /// Creates an instance with element_ct() == xi_size.
  ///
  point_connectivity(size_type xi_size, pod_index_type xstart=0);

  ///
  /// Destructor.
  ///
  virtual ~point_connectivity();

  ///
  /// Static const integral data members.
  /// @hack Inline initialization of static const integral data 
  /// members causes link error in MSC++; use enum instead.
  ///
  enum static_const_int {NODES_PER_ELEMENT = 1}; 

protected:

private:

  //@}


protected:

  ///
  /// Allocates and initializes the connectivity array.
  ///
  void create_connectivity(size_type xi_size, pod_index_type xstart_id);

  // ===========================================================
  /// @name BLOCK_RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The element type.
  ///
  virtual cell_type element_type() const;

protected:

private:

  //@}

  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:
  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual point_connectivity* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

protected:

private:

  //@}

};
  
} // namespace fiber_bundle

#endif // ifndef POINT_CONNECTIVITY_H
