/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include "MouseAction.h"

#include <Scene/Scene.h>
#include <thread>


namespace spix {
namespace cmd {

MouseAction::MouseAction(ItemPosition path, std::vector<MouseTask> mouseTasks)
: m_position(std::move(path))
, m_mouseTasks(mouseTasks)
{
}

void MouseAction::execute(CommandEnvironment& env)
{
    auto path = m_position.itemPath();
    auto item = env.scene().itemAtPath(path);

    if (!item) {
        env.state().reportError("MouseAction: Item not found: " + path.string());
        return;
    }

    auto size = item->size();
    auto mousePoint = m_position.positionForItemSize(size);

    for (auto& task : m_mouseTasks) {
        auto newPoint = mousePoint;
        newPoint.x += task.position.x;
        newPoint.y += task.position.y;

        switch (task.action) {
        case spix::MouseButtonActions::Down: {
            env.scene().events().mouseDown(item.get(), newPoint, task.button);
            break;
          }
        case spix::MouseButtonActions::Up: {
            env.scene().events().mouseUp(item.get(), newPoint, task.button);
            break;
          }
        case spix::MouseButtonActions::None:
          default:{
            env.scene().events().mouseMove(item.get(), newPoint);
            break;
          }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

} // namespace cmd
} // namespace spix
