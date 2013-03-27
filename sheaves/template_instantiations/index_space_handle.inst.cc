// $RCSfile: index_space_handle.inst.cc,v $ $Revision: 1.3 $ $Date $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Explicit instantiations for class index_space_handle.

#include "index_space_handle.impl.h"

#include "ij_product_structure.h"
#include "ijk_product_structure.h"

using namespace sheaf; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================

//==============================================================================
// ij_product_structure
//==============================================================================

template
SHEAF_DLL_SPEC
const sheaf::ij_product_structure&
sheaf::index_space_handle::
product_structure<sheaf::ij_product_structure>() const;

template
SHEAF_DLL_SPEC
sheaf::ij_product_structure&
sheaf::index_space_handle::
product_structure<sheaf::ij_product_structure>();

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_handle::
product_structure_conforms_to<sheaf::ij_product_structure>() const; 

//==============================================================================
// ijk_product_structure
//==============================================================================

template
SHEAF_DLL_SPEC
const sheaf::ijk_product_structure&
sheaf::index_space_handle::
product_structure<sheaf::ijk_product_structure>() const;

template
SHEAF_DLL_SPEC
sheaf::ijk_product_structure&
sheaf::index_space_handle::
product_structure<sheaf::ijk_product_structure>();

template
SHEAF_DLL_SPEC
bool
sheaf::index_space_handle::
product_structure_conforms_to<sheaf::ijk_product_structure>() const; 
