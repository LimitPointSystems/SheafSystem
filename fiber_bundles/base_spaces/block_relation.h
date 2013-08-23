
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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

// Interface for class block_relation

#ifndef BLOCK_RELATION_H
#define BLOCK_RELATION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// Abstract cell relation for a block of zones of a given type.
///
class SHEAF_DLL_SPEC block_relation  : public any
{
public:

  // ===========================================================
  // BLOCK_RELATION FACET
  // ===========================================================

  ///
  /// Cell types.
  ///
  /// LINE refers to a 1d cell ("segment_complex").
  /// TRIANGLE is a triangle produced by dividing a quad
  /// along the diagonal from (logical) lower left to upper right corner.
  ///
  enum cell_type
  {
    POINT,
    LINE,
    QUAD,
    TRIANGLE,
    HEX,
    TETRA,
    CELL_TYPE_END
  };

  ///
  /// Default constructor.
  ///
  block_relation();

  ///
  ///  Destructor.
  ///
  virtual ~block_relation();

  ///
  /// The element (zone) type.
  ///
  virtual cell_type element_type() const = 0;

protected:
private:


  // ===========================================================
  // ANY FACET
  // ===========================================================

public:

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual block_relation* clone() const = 0;

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
};
  
} // namespace fiber_bundle

#endif // ifndef BLOCK_RELATION_H
