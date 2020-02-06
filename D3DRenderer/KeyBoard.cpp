#include "KeyBoard.h"

bool KeyBoard::IsKeyPressed(unsigned char keycode) const
{
 	return keystates[keycode];
}

KeyBoard::Event KeyBoard::ReadKey()
{
	if (keyBuffer.size() > 0u)
	{
		Event e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
	else
	{
		return Event();
	}
}

bool KeyBoard::IsKeyEmpty() const
{
	return keyBuffer.empty();
}

char KeyBoard::ReadChar()
{
	if (charBuffer.size() > 0u)
	{
		unsigned char charCode = charBuffer.front();
		charBuffer.pop();
		return charCode;
	}
	else
	{
		return 0;
	}
}

bool KeyBoard::IsEmptyChar() const
{
	return charBuffer.empty();
}

void KeyBoard::FlushChar()
{
	charBuffer = std::queue<char>();
}

void KeyBoard::FlushKey()
{
	keyBuffer = std::queue<Event>();
}

void KeyBoard::Flush()
{
	FlushKey();
	FlushChar();
}

void KeyBoard::EnableAutoRepeat()
{
	autoRepeatEnabled = true;
}

void KeyBoard::DisableAutoRepeat()
{
	autoRepeatEnabled = false;
}

bool KeyBoard::IsAutoRepeatEnabled() const
{
	return autoRepeatEnabled;
}

void KeyBoard::OnKeyPressed(unsigned char keycode)
{
	keystates[keycode] = true;
	keyBuffer.push(Event(Event::Type::Pressed, keycode));
	TrimBuffer(keyBuffer);
}

void KeyBoard::OnKeyReleased(unsigned char keycode)
{
	keystates[keycode] = false;
	keyBuffer.push(Event(Event::Type::Released, keycode));
	TrimBuffer(keyBuffer);
}

void KeyBoard::OnChar(char character)
{
	charBuffer.push(character);
	TrimBuffer(charBuffer);
}

void KeyBoard::ClearState()
{
	keystates.reset();
}

template <typename T>
void KeyBoard::TrimBuffer(std::queue<T>& buffer)
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}