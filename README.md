# Anki Developer Website

This is the data for the Anki Developer site.
It is auto-generated from markdown source files
using [jekyll](http://jekyllrb.com/), a static site generator.

## Building the site

### Prerequisites

To build the site locally, you'll need to install some prerequisites:

- [bundler ruby gem](http://bundler.io/)
- [pandoc](http://johnmacfarlane.net/pandoc/)

You can download and install pandoc from [here](http://johnmacfarlane.net/pandoc/installing.html).

To install bundler, type:
```
[sudo] gem install bundler
```

Once bundler is installed, you can use it to install jekyll and other dependencies:

```
cd anki.github.io
bundle install --path vendor/bundle
``` 

### Build the site

```
# build the site
bundle exec jekyll build

# start a webserver for testing
bundle exec jekyll server
```

## Development workflow

Edit the text files in Vim, emacs or your editor of choice.
If you're using a mac, we highly recommend [Marked](http://markedapp.com/).
It allows you to preview the HTML live while you edit, which helps
to avoid any formatting errors.

You can tell jekyll to auto-build when changes are detected and
run the webserver to preview the results.

```
bundle exec jekyll server -w &

# kill the backgrounded processes when you're finished
jobs

# in the commands below, m and n represent the numbers for each
# of the backgrounded process
kill %n
```

## License

The following directories and their contents are Copyright Anki, Inc.
You may not use anything therein without permission from Anki, Inc.

- `_posts`
- `assets/anki`

The [Jekyll-bootstrap](https://github.com/dbtek/jekyll-bootstrap-3) files in `_includes/JB` are MIT licensed.
All other directories and files are under the [Apache 2.0 License](http://www.apache.org/licenses/LICENSE-2.0.html).
