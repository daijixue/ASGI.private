#pragma once

namespace ASGI {
	/** Smart pointer for handling referenced counted objects.*/
	template<class T>
	class ref_ptr
	{
	public:
		typedef T element_type;

		ref_ptr() : _ptr(0) {}
		ref_ptr(T* ptr) : _ptr(ptr) { if (_ptr) _ptr->ref(); }
		ref_ptr(const ref_ptr& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->ref(); }
		template<class Other> ref_ptr(const ref_ptr<Other>& rp) : _ptr(rp._ptr) { if (_ptr) _ptr->ref(); }
		~ref_ptr() { if (_ptr) _ptr->unref();  _ptr = 0; }

		ref_ptr& operator = (const ref_ptr& rp)
		{
			assign(rp);
			return *this;
		}

		template<class Other> ref_ptr& operator = (const ref_ptr<Other>& rp)
		{
			assign(rp);
			return *this;
		}

		inline ref_ptr& operator = (T* ptr)
		{
			if (_ptr == ptr) return *this;
			T* tmp_ptr = _ptr;
			_ptr = ptr;
			if (_ptr) _ptr->ref();
			// unref second to prevent any deletion of any object which might
			// be referenced by the other object. i.e rp is child of the
			// original _ptr.
			if (tmp_ptr) tmp_ptr->unref();
			return *this;
		}

		operator T*() const { return _ptr; }
		// comparison operators for ref_ptr.
		bool operator == (const ref_ptr& rp) const { return (_ptr == rp._ptr); }
		bool operator == (const T* ptr) const { return (_ptr == ptr); }
		friend bool operator == (const T* ptr, const ref_ptr& rp) { return (ptr == rp._ptr); }

		bool operator != (const ref_ptr& rp) const { return (_ptr != rp._ptr); }
		bool operator != (const T* ptr) const { return (_ptr != ptr); }
		friend bool operator != (const T* ptr, const ref_ptr& rp) { return (ptr != rp._ptr); }

		bool operator < (const ref_ptr& rp) const { return (_ptr<rp._ptr); }
	public:
		T& operator*() const { return *_ptr; }
		T* operator->() const { return _ptr; }
		T* get() const { return _ptr; }

		bool operator!() const { return _ptr == 0; } // not required
		bool valid() const { return _ptr != 0; }

		/** release the pointer from ownership by this ref_ptr<>, decrementing the objects refencedCount() via unref_nodelete() to prevent the Object
		* object from being deleted even if the reference count goes to zero.  Use when using a local ref_ptr<> to an Object that you want to return
		* from a function/method via a C pointer, whilst preventing the normal ref_ptr<> destructor from cleaning up the object. When using release()
		* you are implicitly expecting other code to take over management of the object, otherwise a memory leak will result. */
		T* release() { T* tmp = _ptr; if (_ptr) _ptr->unref_nodelete(); _ptr = 0; return tmp; }

		void swap(ref_ptr& rp) { T* tmp = _ptr; _ptr = rp._ptr; rp._ptr = tmp; }
	private:
		template<class Other> void assign(const ref_ptr<Other>& rp)
		{
			if (_ptr == rp._ptr) return;
			T* tmp_ptr = _ptr;
			_ptr = rp._ptr;
			if (_ptr) _ptr->ref();
			// unref second to prevent any deletion of any object which might
			// be referenced by the other object. i.e rp is child of the
			// original _ptr.
			if (tmp_ptr) tmp_ptr->unref();
		}

		T* _ptr;
	};

	template<class T> inline
		void swap(ref_ptr<T>& rp1, ref_ptr<T>& rp2) { rp1.swap(rp2); }

	template<class T> inline
		T* get_pointer(const ref_ptr<T>& rp) { return rp.get(); }

	template<class T, class Y> inline
		ref_ptr<T> static_pointer_cast(const ref_ptr<Y>& rp) { return static_cast<T*>(rp.get()); }

	template<class T, class Y> inline
		ref_ptr<T> dynamic_pointer_cast(const ref_ptr<Y>& rp) { return dynamic_cast<T*>(rp.get()); }

	template<class T, class Y> inline
		ref_ptr<T> const_pointer_cast(const ref_ptr<Y>& rp) { return const_cast<T*>(rp.get()); }
}