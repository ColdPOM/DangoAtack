#pragma once
#include "Common.h"


// ---------------------------------------------------------------------------
/// �L�[��Ԃ��擾����N���X
/// ���̃N���X�𗘗p���邱�Ƃɂ��ȒP�ɃL�[��Ԃ��擾���邱�Ƃ��ł��܂�
// ---------------------------------------------------------------------------
class Key
{
private:
	GLFWwindow *window; // �E�B���h�E�n���h��

	bool mPreA;
	bool mNowA;
	bool mPreS;
	bool mNowS;
	bool mPreD;
	bool mNowD;
	bool mPreW;
	bool mNowW;
	bool mPreSpace;
	bool mNowSpace;

public:
	Key(void);
	~Key(void);

	
	void Init(GLFWwindow *win);  // �L�[�N���X�̏�����
	void Update();               // �L�[��Ԃ̍X�V


	// ----------------------------------------------------------------------------
	/// �L�[��Ԃ̎擾
	/// ���ꂼ��̃L�[��Ԃ��擾�ł��܂�
	/// IsDown:�����Ă���, IsPush:�����ꂽ, IsRelease:������, IsUp:�����Ă���
	// ----------------------------------------------------------------------------
	
	// ����������Ă��Ȃ�
	bool NoKey();

	// A�L�[
	inline bool IsDownA() { return mNowA; }
    inline bool IsPushA() { return !mPreA && mNowA; }
    inline bool IsReleaseA() { return mPreA && !mNowA; }
    inline bool IsUpA() { return !mNowA; }

	// S�L�[
	inline bool IsDownS() { return mNowS; }
    inline bool IsPushS() { return !mPreS && mNowS; }
    inline bool IsReleaseS() { return mPreS && !mNowS; }
    inline bool IsUpS() { return !mNowS; }

	// D�L�[
	inline bool IsDownD() { return mNowD; }
    inline bool IsPushD() { return !mPreD && mNowD; }
    inline bool IsReleaseD() { return mPreD && !mNowD; }
    inline bool IsUpD() { return !mNowD; }

	// W�L�[
	inline bool IsDownW() { return mNowW; }
    inline bool IsPushW() { return !mPreW && mNowW; }
    inline bool IsReleaseW() { return mPreW && !mNowW; }
    inline bool IsUpW() { return !mNowW; }

	// Space�L�[
	inline bool IsDownSpace() { return mNowSpace; }
    inline bool IsPushSpace() { return !mPreSpace && mNowSpace; }
    inline bool IsReleaseSpace() { return mPreSpace && !mNowSpace; }
    inline bool IsUpSpace() { return !mNowSpace; }
};

