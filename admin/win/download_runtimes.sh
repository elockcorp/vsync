#!/bin/sh -x

: ' ###_VIRTUALSAFE_CHANGE_TRACKING_START_###
U2FsdGVkX1/AxQ5f3+wIH3b8vQYyFqjd55qOjUrCAle+wmQvTyxNQM4z6qy4BQbC
ItRMl+lWvIwSF5C5bz/Ouk4n+DB97tgpQRMYaITqb29+VilSgwcz9Ne01KogrPdR
x2mM1bzvhXQmhJV4hNRTsHAIUxLyyzXJwzAdlx5PTGxr5vxKTaOvDyvnvQX7z6lv
WYUeXlGZXSQp5eaHFdOl5Qn1qw5t2AfgiUy6MDCMGWyvXrs2yQWds8xhgQnvvGab
u0RLEnWKnd+tBgvgJ8w0a+SRpCdYXU3IXZA5m5xKnrfUKO6mxfrL22GGVBvua16A
F5/aTxtxPlRObVoitRkOrGQB+3qTCf0HCUmQGF466Z59y2VPwxyYemsA0iiOT2KV
Q813D905iwUbK4I6Aq6M6l2QF7zz8+OmEV1K9WrM5AGbITkflqneVCN+SFo/ehWf
/WfVuSy/ACqxn0XVsfvl73iQOYm9eHoGvzuBysT54mHZWe0P+KxXPldmrFme2OEX
2e+eii1pslLkUTnnqwMwZzU8jUXdbucEl1jCTk+RhVSHao9lOacZDeAMrDFHkWLW
xVUKHxi9m/jQB+DgwYPOk2sQrUU5VYt0WbRNGO8y4Hnj8WLHRvWosIG6fI8FGbfL
oCXAudzLSDrGjHD8z5NwE9eP08eXlIHTW2Z4ToVbIezgZccpBTQEP9KxHP50O45e
P63i8QmChTmWH4TOA3O8zKGvu01Q5P49QzB43/iuVDv7PLcxhWE0ODhel3GVrtF3
###_VIRTUALSAFE_CHANGE_TRACKING_END_### '

#VS2017
tmp_path=${1:-/tmp/.vcredist}
mkdir -p $tmp_path

if [ ! -e $tmp_path/vcredist_x64.exe ]; then
    wget -O $tmp_path/vcredist_x64.exe https://download.visualstudio.microsoft.com/download/pr/11100230/15ccb3f02745c7b206ad10373cbca89b/VC_redist.x64.exe
fi

cp -a $tmp_path/vcredist_x64.exe $PWD
