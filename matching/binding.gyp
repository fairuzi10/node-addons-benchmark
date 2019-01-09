{
  "targets": [
    {
      "target_name": "matching-addon",
      "sources": [ "matching-addon.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
