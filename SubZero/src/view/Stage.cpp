#include "Stage.h"

Stage::Stage(QWidget *parent, SubZeroFactory* subZeroFactory) : QWidget(parent) {
    this->subZeroFactory = subZeroFactory;
    subZero = nullptr;
    stageLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    stageLayout->setSizeConstraint(QLayout::SetFixedSize);
}

void Stage::initialize() {
    subZeroFactory->setStage(this);
    this->setLayout(stageLayout);
    this->show();
}

void Stage::setViewContent(std::string type) {
    if (subZero != nullptr && subZero->getView() != nullptr) {
        logger->info("Deleting previous view");
        stageLayout->removeWidget(subZero->getView());
        // Delete SubZero instance
        // Delete and disconnects all associated QWidgets and their respective signals and slots
        delete subZero;
    }
    subZero = subZeroFactory->createSubZero(type);
    subZero->getView()->initialize();
    stageLayout->addWidget(subZero->getView());
    logger->info("New View initialized");
}

QSize Stage::sizeHint() const {
    return subZero->getView()->sizeHint();
}

QSize Stage::minimumSizeHint() const {
    return subZero->getView()->minimumSizeHint();
}

void Stage::switchToGUIView() {
    stage->setViewContent("GUI");
}

void Stage::switchToMenuView() {
    stage->setViewContent("STAGE");
}

Stage::~Stage() {
    delete logger;
    delete stageLayout;
    if (subZero != nullptr) {
        delete subZero;
    }
    delete subZeroFactory;
}
