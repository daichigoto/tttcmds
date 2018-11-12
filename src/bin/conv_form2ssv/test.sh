#!/bin/sh

export REQUEST_METHOD=POST
export CONTENT_TYPE=application/x-www-form-urlencoded
export CONTENT_LENGTH=39577

cat POST_DATA | form2ssv
