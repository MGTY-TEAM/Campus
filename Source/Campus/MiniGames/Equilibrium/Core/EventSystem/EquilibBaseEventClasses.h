#pragma once
namespace EquilibriumGame
{
	template <class... TParams>
	class AbstractEventHandler
	{
	public:
		virtual void call(TParams... params) = 0;

	protected:
		AbstractEventHandler()
		{
			
		}
	};

	template <class... TParams>
	class TEvent
	{
		using TEventHandler = AbstractEventHandler<TParams...>;

	public:
		TEvent() :
		M_Handlers()
		{
			
		}

		~TEvent()
		{
			for (TEventHandler* Handler : M_Handlers)
				delete Handler;
			M_Handlers.clear();
		}

		void operator()(TParams... params)
		{
			for (TEventHandler* Handler : M_Handlers)
				Handler->call(params...);
		}

		void operator+=(TEventHandler& eventHandler)
		{
			M_Handlers.push_back(&eventHandler);
		}

	private:
		std::list<TEventHandler*> M_Handlers;
	};

	template <class TObject, class... TParams>
	class MethodEventHandler : public AbstractEventHandler<TParams...>
	{
		using TMethod = void(TObject::*)(TParams...);

	public:
		MethodEventHandler(TObject& object, TMethod method) :
			AbstractEventHandler<TParams...>(),
			M_Object(object),
			M_Method(method)
		{
		}

		virtual void call(TParams... params) override final
		{
			(M_Object.*M_Method)(params...);
		}

	private:
		TObject& M_Object;
		TMethod M_Method;
	};

	template <class TObject, class... TParams>
	AbstractEventHandler<TParams...>& createMethodEventHandler(TObject& object, void (TObject::*method)(TParams...))
	{
		return *new MethodEventHandler<TObject, TParams...>(object, method);
	}

#define METHOD_HANDLER( Object, Method ) createMethodEventHandler( Object, &Method )
#define MY_METHOD_HANDLER( Method ) METHOD_HANDLER( *this, Method )
}
