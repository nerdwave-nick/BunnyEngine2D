#include "bupch.h"
#include "bunny/Core/LayerStack.h"

bunny::LayerStack::LayerStack()
{}

bunny::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		layer->OnDetach();
		delete layer;
	}
}

void bunny::LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
	m_LayerInsertIndex++;
}

void bunny::LayerStack::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
}

void bunny::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
	if (it != m_Layers.begin() + m_LayerInsertIndex)
	{
		m_Layers.erase(it);
		m_LayerInsertIndex--;
	}
}

void bunny::LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
	if (it != m_Layers.end())
		m_Layers.erase(it);
}
