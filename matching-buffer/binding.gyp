{
  "targets": [
    {
      "target_name": "matching-addon-buffer",
      "sources": [ "matching-addon-buffer.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
