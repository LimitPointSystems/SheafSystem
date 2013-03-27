//
// $RCSfile: fiber_bundles_csharp_binding.i,v $ $Revision: 1.3 $ $Date: 2012/03/01 00:40:36 $
//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Swig module interface for fiber_bundles cluster (csharp version)
//

// Set the module name according to the LPS formula.

%module fiber_bundles_csharp_binding

//=============================================================================
// Ignore directives:
//=============================================================================

// $$HACK Ignore all deep_size functions.  Swig is creating duplicate names.

%ignore *::deep_size;

//=============================================================================

%include "sheaves_csharp_binding.i"
%include "fiber_bundles_common_binding.i"

//=============================================================================
