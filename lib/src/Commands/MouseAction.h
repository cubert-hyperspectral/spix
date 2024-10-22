/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#pragma once

#include <Spix/spix_export.h>

#include "Command.h"
#include <Scene/Events.h>
#include <Spix/Data/ItemPosition.h>

namespace spix {
namespace cmd {

class SPIX_EXPORT MouseAction : public Command {
public:
    MouseAction(ItemPosition path, std::vector<MouseTask> mouseTasks);

    void execute(CommandEnvironment& env) override;

private:
    ItemPosition m_position;
    std::vector<MouseTask> m_mouseTasks;
};

} // namespace cmd
} // namespace spix
