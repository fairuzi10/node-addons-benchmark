{
  "targets": [
    {
      "target_name": "matrix-addon",
      "sources": [ "matrix-addon.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
