
//

//
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
//
// Contains all the template directives for the sheaves component.
//

//=============================================================================
// namespace_poset template directives:
//=============================================================================

//
// Define base space factory directives.
//

%define %base_space_factory_templates(B)

%template(new_base_space_ ## B) fiber_bundle::fiber_bundles_namespace::new_base_space<B>;

%enddef

//
// Define fiber space factory directives.
//

%define %fiber_space_factory_templates(F)

%template(new_fiber_space_ ## F) fiber_bundle::fiber_bundles_namespace::new_fiber_space<F>;

%enddef

//
// Define section space factory directives.
//

%define %section_space_factory_templates(S)

%template(new_section_space_ ## S) fiber_bundle::fiber_bundles_namespace::new_section_space<S>;

%enddef
