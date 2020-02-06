#pragma once
#include "Drawable.h"
#include "IndexBuffer.h"

template <class T>
class DrawableBase : public Drawable
{
protected:
	static bool IsStaticInitialized() 
	{
		return !staticBinds.empty();
	}
	static void AddStaticBind(std::unique_ptr<Bindable> bind)
	{
		staticBinds.push_back(std::move(bind));
	}
	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> buff)
	{
		pIndexBuffer = buff.get();
		staticBinds.push_back(std::move(buff));
	}
	void SetIndexFromStatic()
	{
		for (const auto&b : staticBinds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
			{
				pIndexBuffer = p;
				return;
			}
		}
	}
private:
	const std::vector<std::unique_ptr<Bindable>> & GetStaticBinds() const
	{
		return staticBinds;
	}
private:
	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::staticBinds;