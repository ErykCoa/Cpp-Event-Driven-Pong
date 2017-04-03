#ifndef COMMONEVENTS
#define COMMONEVENTS

#include "Event.h"
#include <string>
#include "enums.h"
#include <chrono>

namespace CE
{
	struct ErrorMessage : public Event {
		ErrorMessage(std::string Message, std::chrono::milliseconds Duration) : Message{ Message }, Duration{ Duration } {};
		ErrorMessage() : Message{}, Duration{0} {};

		const std::chrono::milliseconds Duration;
		const std::string Message;
	};

	struct ChangeGameMode : public Event {

		ChangeGameMode(SelectedGameMode Mode) : Mode{ Mode } {};
		ChangeGameMode() : Mode{ SelectedGameMode::NoneMode } {};

		const SelectedGameMode Mode;
	};

	struct GameTick : public Event {
	};

	struct Synchronize : public Event {
	};

	struct ScoreHasChanged : public Event {
	};

	struct BallHasMoved : public Event {
	};

	struct PrepareFrame : public Event {
	};

	struct RenderFrame : public Event {
	};

	struct NewUserCommand : public Event {
	};

}
#endif
