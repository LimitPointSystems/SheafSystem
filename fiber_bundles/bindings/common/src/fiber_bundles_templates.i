
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
