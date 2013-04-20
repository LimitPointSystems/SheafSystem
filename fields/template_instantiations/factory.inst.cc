
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Implementation for class factory.

#include "factory.impl.h"

#include "field_refinement_policy.h"
#include "field_refiner_family.h"

//#include "barycentric_refiner_family.h"
//#include "edge_centered_refiner_family.h"
//#include "zone_centered_refiner_family.h"

using namespace fields; // Workaround for MS C++ bug.

//============================================================
// EXPLICIT INSTANTIATIONS
//============================================================


template class
SHEAF_DLL_SPEC
sheaf::factory<fields::field_refinement_policy>;


template class
SHEAF_DLL_SPEC
sheaf::factory<fields::field_refiner_family>;

// template class
// SHEAF_DLL_SPEC
// sheaf::block<fields::barycentric_refiner_family*>;

///@issue The following instantiation does not compile because there is
///         no method:
///             barycentric_refiner_family::initialize(namespace_poset&).
///template class sheaf::factory<fields::barycentric_refiner_family>;

// template class sheaf::block<fields::edge_centered_refiner_family*>;

///@todo Add comment for why the following instantiation does not work.

//template class sheaf::factory<fields::edge_centered_refiner_family>;

// template class sheaf::block<fields::zone_centered_refiner_family*>;

///@issue The following instantiation does not compile because there is
///         no method:
///             zone_centered_refiner_family::initialize(namespace_poset&).
///template class sheaf::factory<fields::zone_centered_refiner_family>;

