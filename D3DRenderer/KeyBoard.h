#pragma once
#include <bitset>
#include <queue>

class KeyBoard
{
	friend class Window;

public:
	class Event
	{
	public:
		enum class Type
		{
			Pressed,
			Released,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event()
			:type(Type::Invalid),
			code(0u)
		{}
		Event(Type type, unsigned char code)
			:type(type),
			code(code)
		{}
		bool isPressed() const
		{
			return type == Type::Pressed;
		}
		bool isReleased() const
		{
			return type == Type::Released;
		}

		bool isValid() const
		{
			return type == Type::Invalid;
		}
		unsigned char GetCode() const
		{
			return code;
		}
	};
public:
	KeyBoard() = default;
	KeyBoard(const KeyBoard&) = delete;
	KeyBoard& operator=(const KeyBoard&) = delete;

	bool IsKeyPressed(unsigned char keycode) const;
	Event ReadKey();
	bool IsKeyEmpty() const;
	char ReadChar();
	bool IsEmptyChar() const;
	void FlushChar();
	void FlushKey();
	void Flush();
	void EnableAutoRepeat();
	void DisableAutoRepeat();
	bool IsAutoRepeatEnabled() const;

private:
	void OnKeyPressed(unsigned char keycode);
	void OnKeyReleased(unsigned char keycode);
	void OnChar(char character);
	void ClearState();
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer);
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autoRepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;
};

