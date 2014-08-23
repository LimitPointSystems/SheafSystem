
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

package com.limitpoint.tools.viewer.event;

import com.limitpoimt.tools.viewer.animation.*;

/**
 *
 * Implementation <code>PlayThreadEvent</code> for
 * playing a <code>Script</code>.
 *
 */
public class PlayEvent extends PlayThreadEvent
{
  /**
   * The constructor
   */
  public PlayEvent()
  {}

  /**
   * Handle this <code>PlayEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.initScene();

    if(abort)
      return;

    xplayThread.play();
  }
}
