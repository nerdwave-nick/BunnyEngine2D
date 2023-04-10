#pragma once

#include "bunny/Core/Core.h"
#include "bunny/Events/Event.h"
#include "bunny/Core/Timestep.h"

namespace bunny
{
	class  Layer
	{
	public:
		Layer(const bu_str& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep deltaTime) {}
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {}

		inline const bu_str& GetName() const { return m_DebugName; }
	protected:
		bu_str m_DebugName;
	};
}

