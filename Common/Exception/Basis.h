#pragma once

#include <string>
#include <exception>

#include "Code.h"

namespace Standard
{
	namespace Exception
	{
		////////////////////////////////////////////////////////////////////////////////
		/// @class      CObject
		/// @brief      例外の情報を保持するクラス
		///				⇒ std::exceptionから派生
		////////////////////////////////////////////////////////////////////////////////
		class CObject
			: virtual public std::exception
		{
		public:
			////////////////////////////////////////////////////////////////////////////////
			/// @brief			コンストラクタ
			////////////////////////////////////////////////////////////////////////////////
			CObject() : std::exception("")
			{
				ErrorCode = CodeSuccess;
				DeviceErrorCode = DeviceCodeSuccess;
				Message = "";
			}

			////////////////////////////////////////////////////////////////////////////////
			/// @brief			コンストラクタ
			/// @param[in]		errorCode	エラーコード
			////////////////////////////////////////////////////////////////////////////////
			CObject(int errorCode) : std::exception("")
			{
				// 更新
				Update(errorCode, DeviceCodeSuccess, "");
			}

			////////////////////////////////////////////////////////////////////////////////
			/// @brief			コンストラクタ
			/// @param[in]		errorCode	エラーコード
			/// @param[in]		message	メッセージ
			////////////////////////////////////////////////////////////////////////////////
			CObject(int errorCode, const std::string& message) : std::exception(message.c_str())
			{
				// 更新
				Update(errorCode, DeviceCodeSuccess, message);
			}

			////////////////////////////////////////////////////////////////////////////////
			/// @brief			コンストラクタ
			/// @param[in]		errorCode	エラーコード
			/// @param[in]		deviceErrorCode	機器のエラーコード
			/// @param[in]		message	メッセージ
			////////////////////////////////////////////////////////////////////////////////
			CObject(int errorCode, int deviceErrorCode, const std::string& message) : std::exception(message.c_str())
			{
				// 更新
				Update(errorCode, deviceErrorCode, message);
			}

			////////////////////////////////////////////////////////////////////////////////
			/// @brief			コピー代入演算子
			/// @return			自クラス
			////////////////////////////////////////////////////////////////////////////////
			CObject& operator = (const CObject& object) noexcept
			{
				// 更新
				Update(object.ErrorCode, object.DeviceErrorCode, object.Message);

				return *this;
			}

			////////////////////////////////////////////////////////////////////////////////
			/// @brief			デストラクタ
			////////////////////////////////////////////////////////////////////////////////
			~CObject()
			{

			}

			////////////////////////////////////////////////////////////////////////////////
			/// @brief			メッセージを取得
			///					★継承した関数
			/// @return			メッセージ
			////////////////////////////////////////////////////////////////////////////////
			virtual const char* what() const throw()
			{
				return Message.c_str();
			}

		protected:
			////////////////////////////////////////////////////////////////////////////////
			/// @brief			自クラスを更新
			/// @param[in]		object	自クラス
			////////////////////////////////////////////////////////////////////////////////
			void Update(const CObject& object)
			{
				// 更新
				Update(object.ErrorCode, object.DeviceErrorCode, object.Message);
			}

		private:
			////////////////////////////////////////////////////////////////////////////////
			/// @brief			自クラスを更新
			/// @param[in]		errorCode	エラーコード
			/// @param[in]		deviceErrorCode	機器のエラーコード
			/// @param[in]		message	メッセージ
			////////////////////////////////////////////////////////////////////////////////
			void Update(int errorCode, int deviceErrorCode, const std::string& message)
			{
				this->ErrorCode = errorCode;
				this->DeviceErrorCode = deviceErrorCode;
				this->Message = message;
			}

		public:
			//! エラーコード
			int ErrorCode;

			//! 機器のエラーコード
			int DeviceErrorCode;

			//! メッセージ
			std::string Message;
		};
	}
}