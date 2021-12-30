enum MessageStatus {
  INVALID_HEADER=-1,
  WRONG_RECIPIENT=-2,
  INVALID_MESSAGE_DIGEST=-3,
  INVALID_HEADER_DIGEST=-4,
  VALID_EMAIL=1
};

int const MAXLEN = 100000;
int const LEN = 200;
int const HASHLEN = 40;

/* pre-supplied helper function */
/* generates the SHA1 hash of input string text into output parameter digest */
void text_to_SHA1_digest(const char *text, char *digest);


/* my functions */


/* returns the number of leading zeros it beings with 
* @param digest, a hex string
* @return, num of 0s if string is valid hex number, -1 otherwise
*/
int leading_zeros(char const * const digest);


/* convert content in tilename into hash digest
* @param filename, a string of filename in which content to be hashed
* @param digest, a string of output hash result. if probelmatic, set to "error"
* @return true if hashed successfully, false otherwise
*/
bool file_to_SHA1_digest(char const * const filename, char * const digest);


/* takes in recipient, filename, output result to header
* @param recipient, recipient email address
* @param filename, content to be hashed
* @param header, output header result
* @return, true if file can be opened, false otherwise
*/
bool make_header(char const * const recipient, char const * const filename, 
                 char * const header);

/* check if a header if valid 
* @param header, input header string
* @return, true if valid, false otherwise
*/
bool is_valid_header(char const * const header);

/* check whether email and header email are same
* @param email_address, input email string
* @param header, input header string
* @return, true if same, false otherwise
*/
bool is_same_recipient(char const * const email_address, 
                       char const * const header);

/* check whether digest for a file content and header digest are same
* @param filename, input file containing content to be hashed
* @param header, input header string
* @return, true if same, false otherwise
*/
bool is_right_digest(char const * const filename, char const * const header);

/* check if a header is valid, return specific error number
* @param email_address, input email string
* @param header, input header string
* @param filename, input file containing content to be hashed
* @return, specific MessageStatus
*/
MessageStatus check_header(char const * const email_address, 
                           char const * const header, 
                           char const * const filename);

