
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

/// Implementation for field_stp algebra functions.

//==============================================================================
// NON-MEMBER FUNCTIONS OF ST2 FACET
//==============================================================================

///
void
fields::
symmetric_product(const field_stp& x0, const field_stp& x1, field_stp& xresult,
                  bool xauto_access)
{
  // Preconditions:

  // Body:

  //$$SCRIBBLE: Currently all symmetric_product functions are
  //            "not_implemented()" because the only meaningful
  //            results would be like Sym(st2 (X) st2) = st4.
  //            But we have not yet implemented any st4 classes.

  not_implemented();

  // Postconditions:

  // Exit:

  return;
}


