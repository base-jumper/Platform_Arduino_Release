/*
 * MemberFunctionPtr.h
 *
 * Created: 9/01/2019 9:09:29 AM
 *  Author: nbute
 */ 


#ifndef MEMBERFUNCTIONPTR_H_
#define MEMBERFUNCTIONPTR_H_

#define CALL_MEMBER_FN(object,ptrToMember) ((object).*(ptrToMember))

namespace BaseJumper
{
	struct FuncPtr
	{
		virtual void operator()() const = 0;
	};
	
	template<typename U> struct Func1ArgPtr
	{
		virtual void operator()(U u) const = 0;
	};
	
	template<typename U, typename V> struct Func2ArgPtr
	{
		virtual void operator()(U u, V v) const = 0;
	};
	
	template<typename U, typename V, typename W> struct Func3ArgPtr
	{
		virtual void operator()(U u, V v, W w) const = 0;
	};
	
	struct StaticFuncPtr : public FuncPtr
	{
	public:
		typedef void (*StaticFn)();
	
	private:
		StaticFn p_func;
	
	public:
		StaticFuncPtr(StaticFn p_func_in) : p_func(p_func_in)
		{
		}
	
		void operator()() const override final
		{
			p_func();
		}
	};
	
	template<typename U> struct StaticFunc1ArgPtr : public Func1ArgPtr<U>
	{
	public:
		typedef void (*StaticFn)(U u);
	
	private:
		StaticFn p_func;
	
	public:
		StaticFunc1ArgPtr(StaticFn p_func_in) : p_func(p_func_in)
		{
		}
	
		void operator()(U u) const override final
		{
			p_func(u);
		}
	};
	
	template<typename U, typename V> struct StaticFunc2ArgPtr : public Func2ArgPtr<U,V>
	{
		public:
		typedef void (*StaticFn)(U u, V v);
	
		private:
		StaticFn p_func;
	
		public:
		StaticFunc2ArgPtr(StaticFn p_func_in) : p_func(p_func_in)
		{
		}
	
		void operator()(U u, V v) const override final
		{
			p_func(u,v);
		}
	};
	
	template<typename U, typename V, typename W> struct StaticFunc3ArgPtr : public Func3ArgPtr<U,V,W>
	{
		public:
		typedef void (*StaticFn)(U u, V v, W w);
	
		private:
		StaticFn p_func;
	
		public:
		StaticFunc3ArgPtr(StaticFn p_func_in) : p_func(p_func_in)
		{
		}
	
		void operator()(U u, V v, W w) const override final
		{
			p_func(u,v,w);
		}
	};
	
	template<typename U> struct StaticFunc1ClosurePtr : public FuncPtr
	{
	public:
		typedef void (*StaticFn)(U u);
	
	private:
		StaticFn p_func;
		U u;
	
	public:
		StaticFunc1ClosurePtr(StaticFn p_func_in, U u_in) : p_func(p_func_in), u(u_in)
		{
		}
	
		void operator()() const override final
		{
			p_func(u);
		}
	};
	
	template<typename T> struct MemberFuncPtrT : public FuncPtr
	{
	public:
		typedef void (T::*MemFn)();
	private:
		T* p_obj;
		MemFn p_func;
	public:
		MemberFuncPtrT(T* p_obj_in, MemFn p_func_in) : p_obj(p_obj_in), p_func(p_func_in)
		{
		}
	
		void operator()() const override final
		{
			if (p_obj && p_func)
				CALL_MEMBER_FN(*p_obj,p_func)();
		}
	};
	
	template<typename T, typename U> struct MemberFunc1ArgPtrT : public Func1ArgPtr<U>
	{
	public:
		typedef void (T::*MemFn)(U arg);
	private:
		T* p_obj;
		MemFn p_func;
	public:
		MemberFunc1ArgPtrT(T* p_obj_in, MemFn p_func_in) : p_obj(p_obj_in), p_func(p_func_in)
		{
		}
	
		void operator()(U arg) const override final
		{
			if (p_obj && p_func)
				CALL_MEMBER_FN(*p_obj,p_func)(arg);
		}
	};
	
	template<typename T, typename U, typename V> struct MemberFunc2ArgPtrT : public Func2ArgPtr<U,V>
	{
		public:
		typedef void (T::*MemFn)(U u, V v);
		private:
		T* p_obj;
		MemFn p_func;
		public:
		MemberFunc2ArgPtrT(T* p_obj_in, MemFn p_func_in) : p_obj(p_obj_in), p_func(p_func_in)
		{
		}
	
		void operator()(U u, V v) const override final
		{
			if (p_obj && p_func)
				CALL_MEMBER_FN(*p_obj,p_func)(u,v);
		}
	};
	
	template<typename T, typename U, typename V, typename W> struct MemberFunc3ArgPtrT : public Func3ArgPtr<U,V,W>
	{
		public:
		typedef void (T::*MemFn)(U u, V v, W w);
		private:
		T* p_obj;
		MemFn p_func;
		public:
		MemberFunc3ArgPtrT(T* p_obj_in, MemFn p_func_in) : p_obj(p_obj_in), p_func(p_func_in)
		{
		}
	
		void operator()(U u, V v, W w) const override final
		{
			if (p_obj && p_func)
			CALL_MEMBER_FN(*p_obj,p_func)(u,v,w);
		}
	};
	
	template<typename T, typename U> struct MemberFunc1ClosurePtrT : public FuncPtr
	{
		public:
		typedef void (T::*MemFn)(U u);
		private:
		T* p_obj;
		MemFn p_func;
		U u;
	
		public:
		MemberFunc1ClosurePtrT(T* p_obj_in, MemFn p_func_in, U u_in)
		: p_obj(p_obj_in), p_func(p_func_in), u(u_in)
		{
		}
	
		void operator()() const override final
		{
			if (p_obj && p_func)
				CALL_MEMBER_FN(*p_obj,p_func)(u);
		}
	};
	
	template<typename T, typename U, typename V> struct MemberFunc2ClosuresPtrT : public FuncPtr
	{
	public:
		typedef void (T::*MemFn)(U u, V v);
	private:
		T* p_obj;
		MemFn p_func;
		U u;
		V v;
	
		public:
		MemberFunc2ClosuresPtrT(T* p_obj_in, MemFn p_func_in, U u_in, V v_in) 
		: p_obj(p_obj_in), p_func(p_func_in), u(u_in), v(v_in)
		{
		}
	
		void operator()() const override final
		{
			if (p_obj && p_func)
				CALL_MEMBER_FN(*p_obj,p_func)(u,v);
		}
	};
	
	struct NullFuncPtr : public FuncPtr
	{
		void operator()() const override final
		{
			// do nothing
		}
	};
	
	template <typename T>
	struct NullFunc1ArgPtr : public Func1ArgPtr<T>
	{
		void operator()(T t) const override final
		{
			// do nothing
		}
	};
	
	extern NullFuncPtr null_func_ptr;
}

#endif /* MEMBERFUNCTIONPTR_H_ */
