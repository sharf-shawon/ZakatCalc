#!/bin/bash

set -euo pipefail

HTML_FILE="./index.html"
INO_FILE="./ZakatCalc.ino"
TMP_PLACEHOLDER="scripts/zakat_html_placeholder.tmp"

# Minify index.html to a single line
MINIFIED_HTML=$(html-minifier "$HTML_FILE" \
  --collapse-whitespace \
  --remove-comments \
  --minify-js \
  --minify-css \
  --remove-optional-tags \
  --remove-redundant-attributes \
  --remove-script-type-attributes \
  --remove-tag-whitespace \
  --use-short-doctype)

if [[ -z "$MINIFIED_HTML" ]]; then
  echo "Failed to minify index.html"
  exit 1
fi

# Write minified HTML to a temp file (no escaping needed)
printf '%s\n' "$MINIFIED_HTML" > "$TMP_PLACEHOLDER"

# Replace the placeholder line with the temp file content
sed -i.bak "
/{{ZAKAT_HTML_PLACEHOLDER}}/{
  r $TMP_PLACEHOLDER
  d
}
" "$INO_FILE"

rm -f "$TMP_PLACEHOLDER" "${INO_FILE}.bak"

git add "$INO_FILE"
echo "Updated ZakatCalc.ino with minified index.html"
