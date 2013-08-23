
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

package tools.viewer.render;

import bindings.java.*;
import java.io.*;

import vtk.*;

/**
 *
 * Struct which describes a <code>LookupTable</code>
 *
 */
public abstract class LookupTableDescriptor extends Descriptor
{
  /**
   * Clone this <code>LookupTableDescriptor</code>
   */
  public abstract LookupTableDescriptor clone();

  /**
   * Copy the values of xlookupTable into this
   * <code>LookupTableDescriptor</code>.
   */
  public abstract void copy(LookupTableDescriptor xlookupTable);

  /**
   * Build a <code>LookupTable</code> from this
   * <code>LookupTableDescriptor</code>.
   */
  public abstract LookupTable build(namespace_poset xnamespace);

  /**
   * Update xlookupTable to this <code>LookupTableDescriptor</code>
   */
  public abstract void update(LookupTable xlookupTable,
                              LookupTableDescriptor xdescriptor);
}
