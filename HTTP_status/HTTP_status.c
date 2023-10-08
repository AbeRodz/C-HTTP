// http_statuses.c

#include "HTTP_status.h"

// Define HTTP status text strings
static const char *http_status_texts[] = {
    [HTTP_STATUS_CONTINUE] = "Continue",
    [HTTP_STATUS_SWITCHING_PROTOCOLS] = "Switching Protocols",
    [HTTP_STATUS_PROCESSING] = "Processing",
    [HTTP_STATUS_EARLY_HINTS] = "Early Hints",
    [HTTP_STATUS_OK] = "OK",
    [HTTP_STATUS_CREATED] = "Created",
    [HTTP_STATUS_ACCEPTED] = "Accepted",
    [HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION] = "Non-Authoritative Information",
    [HTTP_STATUS_NO_CONTENT] = "No Content",
    [HTTP_STATUS_RESET_CONTENT] = "Reset Content",
    [HTTP_STATUS_PARTIAL_CONTENT] = "Partial Content",
    [HTTP_STATUS_MULTI_STATUS] = "Multi-Status",
    [HTTP_STATUS_ALREADY_REPORTED] = "Already Reported",
    [HTTP_STATUS_IM_USED] = "IM Used",
    [HTTP_STATUS_MULTIPLE_CHOICES] = "Multiple Choices",
    [HTTP_STATUS_MOVED_PERMANENTLY] = "Moved Permanently",
    [HTTP_STATUS_FOUND] = "Found",
    [HTTP_STATUS_SEE_OTHER] = "See Other",
    [HTTP_STATUS_NOT_MODIFIED] = "Not Modified",
    [HTTP_STATUS_USE_PROXY] = "Use Proxy",
    [HTTP_STATUS_TEMPORARY_REDIRECT] = "Temporary Redirect",
    [HTTP_STATUS_PERMANENT_REDIRECT] = "Permanent Redirect",
    [HTTP_STATUS_BAD_REQUEST] = "Bad Request",
    [HTTP_STATUS_UNAUTHORIZED] = "Unauthorized",
    [HTTP_STATUS_PAYMENT_REQUIRED] = "Payment Required",
    [HTTP_STATUS_FORBIDDEN] = "Forbidden",
    [HTTP_STATUS_NOT_FOUND] = "Not Found",
    [HTTP_STATUS_METHOD_NOT_ALLOWED] = "Method Not Allowed",
    [HTTP_STATUS_NOT_ACCEPTABLE] = "Not Acceptable",
    [HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED] = "Proxy Authentication Required",
    [HTTP_STATUS_REQUEST_TIMEOUT] = "Request Timeout",
    [HTTP_STATUS_CONFLICT] = "Conflict",
    [HTTP_STATUS_GONE] = "Gone",
    [HTTP_STATUS_LENGTH_REQUIRED] = "Length Required",
    [HTTP_STATUS_PRECONDITION_FAILED] = "Precondition Failed",
    [HTTP_STATUS_PAYLOAD_TOO_LARGE] = "Payload Too Large",
    [HTTP_STATUS_URI_TOO_LONG] = "URI Too Long",
    [HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type",
    [HTTP_STATUS_RANGE_NOT_SATISFIABLE] = "Range Not Satisfiable",
    [HTTP_STATUS_EXPECTATION_FAILED] = "Expectation Failed",
    [HTTP_STATUS_IM_A_TEAPOT] = "I'm a teapot",
    [HTTP_STATUS_MISDIRECTED_REQUEST] = "Misdirected Request",
    [HTTP_STATUS_UNPROCESSABLE_ENTITY] = "Unprocessable Entity",
    [HTTP_STATUS_LOCKED] = "Locked",
    [HTTP_STATUS_FAILED_DEPENDENCY] = "Failed Dependency",
    [HTTP_STATUS_UPGRADE_REQUIRED] = "Upgrade Required",
    [HTTP_STATUS_PRECONDITION_REQUIRED] = "Precondition Required",
    [HTTP_STATUS_TOO_MANY_REQUESTS] = "Too Many Requests",
    [HTTP_STATUS_REQUEST_HEADER_FIELDS_TOO_LARGE] = "Request Header Fields Too Large",
    [HTTP_STATUS_UNAVAILABLE_FOR_LEGAL_REASONS] = "Unavailable For Legal Reasons",
    [HTTP_STATUS_INTERNAL_SERVER_ERROR] = "Internal Server Error",
    [HTTP_STATUS_NOT_IMPLEMENTED] = "Not Implemented",
    [HTTP_STATUS_BAD_GATEWAY] = "Bad Gateway",
    [HTTP_STATUS_SERVICE_UNAVAILABLE] = "Service Unavailable",
    [HTTP_STATUS_GATEWAY_TIMEOUT] = "Gateway Timeout",
    [HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED] = "HTTP Version Not Supported",
    [HTTP_STATUS_VARIANT_ALSO_NEGOTIATES] = "Variant Also Negotiates",
    [HTTP_STATUS_INSUFFICIENT_STORAGE] = "Insufficient Storage",
    [HTTP_STATUS_LOOP_DETECTED] = "Loop Detected",
    [HTTP_STATUS_NOT_EXTENDED] = "Not Extended",
    [HTTP_STATUS_NETWORK_AUTHENTICATION_REQUIRED] = "Network Authentication Required"};

// Function to get HTTP status text based on the status code
const char *get_http_status_text(int status_code)
{
    const char *status_text = http_status_texts[status_code];
    return status_text ? status_text : "Unknown Status";
}
