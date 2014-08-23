
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

package com.limitpoint.tools.viewer.user;

import com.limitpoimt.tools.viewer.render.*;

import javax.swing.*;

/**
 *
 * 3D implementation of <code>DescriptorsTabbedPane</code> for
 * containing the script panels for the <code>Viewer</code>
 *
 */
public class G2DDescriptorsTabbedPane extends DescriptorsTabbedPane
{
  /**
   * Default constructor
   */
  protected G2DDescriptorsTabbedPane(G2DViewer xviewer)
  {
    super(xviewer);
  }
}
