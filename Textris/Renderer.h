#ifndef _RENDERER_CLASS
#define _RENDERER_CLASS

class Renderer
{
private:
	HANDLE mv_hBuffer[2];	//화면 버퍼 핸들
	int mv_nScreenIndex;	//현재 출력될 버퍼
	const short mv_sMAXLINE;
	const short mv_sMAXWORD;

public:
	Renderer(const short sMaxWord, const short sMaxline);
	~Renderer();

	void UpdateBuffer(const std::wstring *pwStr, const size_t &count);
	void UpdateBuffer(const std::wstring *pwStr, const size_t &count, const short cursorX);
	void Rendering();
	void ResetBuffer();
};

#endif