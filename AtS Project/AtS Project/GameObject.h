#pragma once
#include <map>
#include <vector>
#include "Transform.h"
#include "GameObjectsCollection.h"


class GameObject
{
public:
	GameObject(const std::string& name)
		: m_name{ name }, m_layer(0)
	{}

	GameObject() {}

	~GameObject() {}

	void* operator new(size_t size)
	{
		return GameObjectsCollection::get().gameObject();
	}

	friend GameObject* GameObjectsCollection::gameObject(std::string name);

	template<class T>
	T* AddComponent() { return GameObjectsCollection::get().AddComponent<T>(this, m_id); }

	template<class T>
	T* GetComponent() const { return GameObjectsCollection::get().GetComponent<T>(m_id); }

	template<class T>
	bool HasComponent() const { return GameObjectsCollection::get().HasComponent<T>(m_id); }

	template<class T>
	void RemoveComponent() { GameObjectsCollection::get().RemoveComponent<T>(m_id); }

	std::string name() { return m_name; }
	std::string tag() { return m_tag; }
	unsigned int id() { return m_id; }
	unsigned int scene() { return m_sceneId; }

	unsigned int layer() { return m_layer; }
	void layer(unsigned int layer) { GameObjectsCollection::get().SetObjectLayer(m_tag, layer); }

	Transform transform;

private:
	unsigned int m_id;
	std::string m_name;

	std::string m_tag;
	unsigned int m_sceneId;
	unsigned int m_layer;
};