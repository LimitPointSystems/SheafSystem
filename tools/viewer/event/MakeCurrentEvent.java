
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

package tools.viewer.event;

import tools.viewer.render.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * making the interactor current.
 *
 */
public class MakeCurrentEvent extends RenderThreadEvent
{
  /**
   * The constructor
   */
  public MakeCurrentEvent()
  {}

  /**
   * Handle this <code>MakeCurrentEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.makeCurrent();
  }
}
