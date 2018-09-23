#pragma once

using namespace std;

enum class ErrorCode {
	ok = 200,
	BadRequest = 400,
	NotFound = 404,
	TooManyRequests = 429
};

struct _response{
	ErrorCode code;
	string str;
};

typedef _response Response;
