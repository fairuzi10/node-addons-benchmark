{
  "targets": [
    {
      "target_name": "set",
      "sources": [ "set-addon.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
